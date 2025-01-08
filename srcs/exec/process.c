/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 11:39:41 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/08 12:02:37 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* static int	is_builtins(t_cmd *cmd) */
/* { */
/* 	int	n; */
/**/
/* 	n = ft_strlen(cmd->args[0]); */
/* 	if (ft_strncmp(cmd->args[0], "echo", n) == 0) */
/* 		return (1); */
/* 	else if (ft_strncmp(cmd->args[0], "cd", n) == 0) */
/* 		return (1); */
/* 	else if (ft_strncmp(cmd->args[0], "pwd", n) == 0) */
/* 		return (1); */
/* 	else if (ft_strncmp(cmd->args[0], "export", n) == 0) */
/* 		return (1); */
/* 	else if (ft_strncmp(cmd->args[0], "unset", n) == 0) */
/* 		return (1); */
/* 	else if (ft_strncmp(cmd->args[0], "env", n) == 0) */
/* 		return (1); */
/* 	else if (ft_strncmp(cmd->args[0], "ezit", n) == 0) */
/* 		return (1); */
/* 	return (0); */
/* } */

void	process(t_cmd *cmd, char **envp)
{
	char	*cmd_path;

	/* if (is_builtins(cmd)) */
	/* 	exec_builtins(cmd); */
	cmd_path = get_cmd_path(cmd->args[0], envp);
	if (!cmd_path)
	{
		perror("Command not found");
		exit(EXIT_FAILURE);
	}
	execve(cmd_path, cmd->args, envp);
	free(cmd_path);
	free_tab(cmd->args);
}
