/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_processes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 11:38:01 by ltheveni          #+#    #+#             */
/*   Updated: 2025/02/02 12:29:27 by ltheveni         ###   ########.fr       */
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

static void	close_pipe(int pipe_in, int *fd)
{
	if (pipe_in != -1)
		close(pipe_in);
	if (fd[1] != -1)
		close(fd[1]);
}

static void	cleanup_fork(t_cmd *cmd, t_shell *shell, int *fd, int pipe_in)
{
	t_redirects	*current;

	current = cmd->redirects;
	while (current)
	{
		if (current->is_here_doc && current->infile)
			unlink(cmd->redirects->infile);
		current = current->next;
	}
	close_pipe(pipe_in, fd);
	if (fd[0] != -1)
		close(fd[0]);
	free_cmd_node(cmd);
	free_shell(shell);
	shell->last_exit = EXIT_SUCCESS;
	exit(EXIT_SUCCESS);
}

static void	redirect_pipes(int pipe, int std)
{
	if (pipe != -1)
	{
		if (dup2(pipe, std) == -1)
			dup2_exit("dup2 (redirect)");
		close(pipe);
	}
}

void	fork_processes(t_cmd *cmd, t_shell *shell, int *fd, int pipe_in)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		setup_signals(0);
		if (pipe_in != -1)
			redirect_pipes(pipe_in, STDIN_FILENO);
		if (cmd->next)
			redirect_pipes(fd[1], STDOUT_FILENO);
		redirect_input(cmd, shell, -1);
		redirect_output(cmd, shell);
		if (is_builtins(cmd))
			exec_builtins(shell, cmd);
		else if (cmd->args[0])
			process(cmd, shell, pipe_in, fd);
		cleanup_fork(cmd, shell, fd, pipe_in);
	}
	else if (pid > 0)
	{
		close_pipe(pipe_in, fd);
		shell->pid = pid;
	}
	else if (pid == -1)
		handle_fork_error(cmd, shell);
}
