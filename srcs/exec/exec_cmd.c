/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 14:06:28 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/27 15:50:49 by ltheveni         ###   ########.fr       */
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

static void	setup_fd(t_shell *shell, t_cmd *current, int *fd)
{
	if (current->next)
		setup_pipe(fd, current, shell);
	else
	{
		fd[0] = -1;
		fd[1] = -1;
	}
}

static void	wait_for_child(t_shell *shell)
{
	int		status;
	int		signal;
	pid_t	pid;

	pid = wait(&status);
	while (pid > 0)
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
		pid = wait(&status);
	}
}

static void	exec_cmd_loop(t_cmd *cmd, t_shell *shell, int *fd, int pipe_in)
{
	t_cmd	*current;

	current = cmd;
	while (current)
	{
		setup_fd(shell, cmd, fd);
		if (is_builtins(current) && (!current->next && pipe_in == -1))
		{
			if (is_parent_builtins(current))
			{
				exec_builtins(shell, cmd);
				current = current->next;
				continue ;
			}
		}
		fork_processes(current, shell, fd, pipe_in);
		pipe_in = fd[0];
		if (current->next)
			close(fd[1]);
		current = current->next;
	}
	if (fd[0] != -1)
		close(fd[0]);
}

void	exec_cmd(t_cmd *cmd, t_shell *shell)
{
	int	fd[2];
	int	pipe_in;

	pipe_in = -1;
	exec_cmd_loop(cmd, shell, fd, pipe_in);
	wait_for_child(shell);
}
