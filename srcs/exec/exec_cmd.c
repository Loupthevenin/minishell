/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 14:06:28 by ltheveni          #+#    #+#             */
/*   Updated: 2025/02/02 21:02:07 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	setup_fd(t_shell *shell, t_cmd *current, int *fd)
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

static void	close_pipes(int *pipe_in, int *fd, t_cmd *current)
{
	if (*pipe_in != -1)
		close(*pipe_in);
	*pipe_in = fd[0];
	if (current->next && fd[1] != -1)
		close(fd[1]);
}

static void	exec_cmd_loop(t_cmd *cmd, t_shell *shell, int *fd, int pipe_in)
{
	t_cmd	*current;

	current = cmd;
	while (current)
	{
		setup_fd(shell, cmd, fd);
		if (check_file_permission(current, shell))
		{
			if (is_builtins(current) && (!current->next && pipe_in == -1)
				&& is_parent_builtins(cmd))
			{
				exec_builtins(shell, cmd);
				current = current->next;
				continue ;
			}
			fork_processes(current, shell, fd, pipe_in);
		}
		close_pipes(&pipe_in, fd, current);
		current = current->next;
	}
	if (fd[0] != -1)
		close(fd[0]);
}

void	exec_cmd(t_cmd *cmd, t_shell *shell)
{
	int	fd[2];
	int	pipe_in;

	if (!cmd)
		return ;
	pipe_in = -1;
	if (!check_here_docs(cmd, shell))
		return ;
	exec_cmd_loop(cmd, shell, fd, pipe_in);
	wait_for_child(shell);
}
