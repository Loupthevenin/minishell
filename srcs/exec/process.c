/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 11:39:41 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/10 10:26:03 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	process(t_cmd *cmd, char **envp)
{
	char	*cmd_path;

	cmd_path = get_cmd_path(cmd->args[0], envp);
	if (!cmd_path)
	{
		ft_putstr_fd(cmd->args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		free_cmd_node(cmd);
		exit(127);
	}
	execve(cmd_path, cmd->args, envp);
	perror("execve");
	free(cmd_path);
	free_tab(cmd->args);
	exit(EXIT_FAILURE);
}
