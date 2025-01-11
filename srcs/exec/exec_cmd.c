/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 14:06:28 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/11 12:06:43 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	t_cmd	*current;
	int		i;

	current = cmd;
	shell->n_pipes = get_command_count(cmd) - 1;
	shell->pipefd = malloc(sizeof(int *) * shell->n_pipes);
	if (!shell->pipefd)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < shell->n_pipes)
	{
		shell->pipefd[i] = malloc(sizeof(int) * 2);
		if (pipe(shell->pipefd[i]) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	exec_cmd(t_cmd *cmd, t_shell *shell)
{
	create_pipes(cmd, shell);
	fork_processes(cmd, shell);
	close_pipes(shell->pipefd, shell->n_pipes);
	// close infile outfile;
	wait_for_children(cmd);
}
