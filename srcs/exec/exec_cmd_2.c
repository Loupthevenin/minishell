/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:04:33 by ltheveni          #+#    #+#             */
/*   Updated: 2025/02/03 11:12:49 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	setup_fd(t_shell *shell, t_cmd *current, int *fd)
{
	if (current->next)
	{
		if (pipe(fd) == -1)
		{
			perror("pipe failed");
			if (fd[0] != -1)
				close(fd[0]);
			if (fd[1] != -1)
				close(fd[1]);
			free_cmd_node(current);
			free_shell(shell);
			shell->last_exit = EXIT_FAILURE;
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		fd[0] = -1;
		fd[1] = -1;
	}
}

void	close_pipes(int *pipe_in, int *fd, t_cmd *current)
{
	if (*pipe_in != -1)
		close(*pipe_in);
	*pipe_in = fd[0];
	if (current->next && fd[1] != -1)
		close(fd[1]);
}

void	wait_for_child(t_shell *shell)
{
	int		status;
	int		signal;
	pid_t	pid;

	pid = waitpid(shell->pid, &status, 0);
	if (pid > 0)
	{
		if (pid == shell->pid)
		{
			if (WIFEXITED(status))
				shell->last_exit = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				signal = WTERMSIG(status);
				shell->last_exit = 128 + signal;
				if (signal == SIGQUIT)
					ft_putstr_fd("Quit: 3\n", 2);
			}
		}
		pid = waitpid(-1, &status, 0);
	}
	if (shell->last_exit != 130)
		g_signal = 0;
}
