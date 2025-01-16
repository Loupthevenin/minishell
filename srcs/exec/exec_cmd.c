/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 14:06:28 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/16 15:37:45 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	setup_pipe(int *fd, t_cmd *cmd, t_shell *shell)
{
	if (pipe(fd) == -1)
	{
		perror("pipe failed");
		if (fd[0] != -1)
			close(fd[0]);
		if (fd[1] != -1)
			close(fd[1]);
		free_cmd_node(cmd);
		free_shell(shell);
		shell->last_exit = EXIT_FAILURE;
		exit(EXIT_FAILURE);
	}
}

static void	wait_for_child(void)
{
	int		status;
	pid_t	pid;

	while ((pid = wait(&status)) > 0)
	{
	}
}

void	exec_cmd(t_cmd *cmd, t_shell *shell)
{
	t_cmd	*current;
	int		fd[2];
	int		pipe_in;

	pipe_in = -1;
	current = cmd;
	while (current)
	{
		if (current->next)
			setup_pipe(fd, current, shell);
		else
		{
			fd[0] = -1;
			fd[1] = -1;
		}
		/* if (is_builtins(current)) */
		/* { */
		/* 	exec_builtins(cmd); */
		/* 	current = current->next; */
		/* 	continue ; */
		/* } */
		fork_processes(current, shell, fd, pipe_in);
		pipe_in = fd[0];
		if (current->next)
			close(fd[1]);
		current = current->next;
	}
	wait_for_child();
}
