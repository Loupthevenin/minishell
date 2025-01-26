/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_processes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 11:38:01 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/26 10:05:26 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle_fork_error(t_cmd *cmd, t_shell *shell)
{
	perror("fork");
	free_cmd_node(cmd);
	free_shell(shell);
	shell->last_exit = EXIT_FAILURE;
	exit(EXIT_FAILURE);
}

static void	cleanup_fork(t_cmd *cmd, t_shell *shell)
{
	if (cmd->is_here_doc && cmd->infile)
		unlink(cmd->infile);
	free_cmd_node(cmd);
	free_shell(shell);
	shell->last_exit = EXIT_SUCCESS;
	exit(EXIT_SUCCESS);
}

static void	close_pipe(int pipe_in, int *fd)
{
	if (pipe_in != -1)
		close(pipe_in);
	if (fd[1] != -1)
		close(fd[1]);
}

void	fork_processes(t_cmd *cmd, t_shell *shell, int *fd, int pipe_in)
{
	shell->pid = fork();
	if (shell->pid == 0)
	{
		setup_signals(0);
		if (cmd->infile || cmd->is_here_doc)
			redirect_input(cmd, shell, -1);
		else if (pipe_in != -1)
			redirect_input(cmd, shell, pipe_in);
		if (cmd->outfile)
			redirect_output(cmd, shell, -1);
		else if (cmd->next)
			redirect_output(cmd, shell, fd[1]);
		process(cmd, shell);
		cleanup_fork(cmd, shell);
	}
	else if (shell->pid == -1)
		handle_fork_error(cmd, shell);
	close_pipe(pipe_in, fd);
}
