/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_processes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 11:38:01 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/11 15:21:39 by ltheveni         ###   ########.fr       */
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
	perror("fork");
	free_cmd_node(cmd);
	free_tab((void **)shell->pipefd, shell->n_pipes, 0);
	exit(EXIT_FAILURE);
}

void	fork_processes(t_cmd *cmd, t_shell *shell)
{
	t_cmd	*current;
	int		i;

	current = cmd;
	i = 0;
	while (current)
	{
		/* if (is_builtins(current)) */
		/* { */
		/* 	exec_builtins(cmd); */
		/* 	current = current->next; */
		/* 	continue ; */
		/* } */
		shell->pid = fork();
		if (shell->pid == -1)
			handle_fork_error(cmd, shell);
		if (shell->pid == 0)
		{
			redirect(i, cmd, shell);
			process(cmd, shell);
			exit(EXIT_SUCCESS);
		}
		current = current->next;
		i++;
	}
}
