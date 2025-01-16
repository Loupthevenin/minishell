/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_processes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 11:38:01 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/16 12:22:39 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* static int	is_builtins(t_cmd *cmd) */
/* { */
/* 	if (!ft_strcmp(cmd->args[0], "echo")) */
/* 		return (1); */
/* 	else if (!ft_strcmp(cmd->args[0], "cd")) */
/* 		return (1); */
/* 	else if (!ft_strcmp(cmd->args[0], "pwd")) */
/* 		return (1); */
/* 	else if (!ft_strcmp(cmd->args[0], "export")) */
/* 		return (1); */
/* 	else if (!ft_strcmp(cmd->args[0], "unset")) */
/* 		return (1); */
/* 	else if (!ft_strcmp(cmd->args[0], "env")) */
/* 		return (1); */
/* 	else if (!ft_strcmp(cmd->args[0], "exit")) */
/* 		return (1); */
/* 	return (0); */
/* } */

static void	handle_fork_error(t_cmd *cmd, t_shell *shell)
{
	(void)shell;
	perror("fork");
	free_cmd_node(cmd);
	exit(EXIT_FAILURE);
}

static void	cleanup_fork(t_cmd *cmd, t_shell *shell)
{
	(void)shell;
	free_cmd_node(cmd);
}

void	fork_processes(t_cmd *cmd, t_shell *shell, int *fd, int pipe_in)
{
	/* if (is_builtins(current)) */
	/* { */
	/* 	exec_builtins(cmd); */
	/* 	current = current->next; */
	/* 	continue ; */
	/* } */
	shell->pid = fork();
	if (shell->pid == 0)
	{
		setup_signals(0);
		if (pipe_in != -1)
			redirect_input(cmd, pipe_in);
		if (fd[1] != -1)
			redirect_output(cmd, fd[1]);
		if (pipe_in != -1)
			close(pipe_in);
		if (fd[1] != -1)
			close(fd[1]);
		process(cmd, shell);
		cleanup_fork(cmd, shell);
		exit(EXIT_SUCCESS);
	}
	else if (shell->pid == -1)
		handle_fork_error(cmd, shell);
	if (pipe_in != -1)
		close(pipe_in);
	if (fd[1] != -1)
		close(fd[1]);
}
