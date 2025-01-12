/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 14:06:28 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/12 18:59:50 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle_pipes_error(t_cmd *cmd, t_shell *shell, int i)
{
	perror("pipe");
	free_cmd_node(cmd);
	free_tab((void **)shell->pipefd, i + 1, 0);
	exit(EXIT_FAILURE);
}

static void	wait_for_children(t_cmd *cmd)
{
	t_cmd	*current;

	current = cmd;
	while (current)
	{
		wait(NULL);
		current = current->next;
	}
}

static void	create_pipes(t_cmd *cmd, t_shell *shell)
{
	int	i;

	shell->n_pipes = get_command_count(cmd) - 1;
	shell->pipefd = malloc(sizeof(int *) * shell->n_pipes);
	if (!shell->pipefd)
	{
		perror("malloc");
		free_cmd_node(cmd);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < shell->n_pipes)
	{
		shell->pipefd[i] = malloc(sizeof(int) * 2);
		if (!shell->pipefd[i])
			handle_pipes_error(cmd, shell, i);
		if (pipe(shell->pipefd[i]) == -1)
			handle_pipes_error(cmd, shell, i);
		i++;
	}
}

void	exec_cmd(t_cmd *cmd, t_shell *shell)
{
	create_pipes(cmd, shell);
	fork_processes(cmd, shell);
	if (cmd->infile >= 0)
		close(cmd->infile);
	if (cmd->outfile >= 0)
		close(cmd->outfile);
	close_pipes(shell->pipefd, shell->n_pipes);
	wait_for_children(cmd);
}
