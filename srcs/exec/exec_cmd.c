/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 14:06:28 by ltheveni          #+#    #+#             */
/*   Updated: 2025/02/03 11:36:03 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle_check_file(int *pipe_in, int *fd, t_cmd **current,
		int *has_error)
{
	close_pipes(pipe_in, fd, *current);
	*current = (*current)->next;
	*has_error = 1;
}

static void	exec_fork_close(t_cmd **current, t_shell *shell, int *fd,
		int *pipe_in)
{
	fork_processes(*current, shell, fd, *pipe_in);
	close_pipes(pipe_in, fd, *current);
	*current = (*current)->next;
}

static void	close_and_wait(int has_error, int *fd, t_shell *shell)
{
	if (fd[0] != -1)
		close(fd[0]);
	if (!has_error)
		wait_for_child(shell);
}

static void	exec_cmd_loop(t_cmd *cmd, t_shell *shell, int *fd, int pipe_in)
{
	t_cmd	*current;
	int		has_error;

	current = cmd;
	has_error = 0;
	while (current)
	{
		setup_fd(shell, cmd, fd);
		if (!check_file_permission(current, shell))
		{
			handle_check_file(&pipe_in, fd, &current, &has_error);
			continue ;
		}
		has_error = 0;
		if (is_builtins(current) && (!current->next && pipe_in == -1)
			&& is_parent_builtins(cmd))
		{
			exec_builtins(shell, cmd);
			current = current->next;
			continue ;
		}
		exec_fork_close(&current, shell, fd, &pipe_in);
	}
	close_and_wait(has_error, fd, shell);
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
}
