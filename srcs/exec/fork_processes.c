/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_processes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 11:38:01 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/09 18:26:04 by ltheveni         ###   ########.fr       */
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

void	fork_processes(t_cmd *cmd, char **envp)
{
	pid_t	pid;
	t_cmd	*current;

	current = cmd;
	while (current)
	{
		/* if (is_builtins(current)) */
		/* { */
		/* 	exec_builtins(cmd); */
		/* 	current = current->next; */
		/* 	continue ; */
		/* } */
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			process(cmd, envp);
			exit(EXIT_SUCCESS);
		}
		current = current->next;
	}
}
