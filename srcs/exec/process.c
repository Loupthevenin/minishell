/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 11:39:41 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/11 11:24:07 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	process(t_cmd *cmd, t_shell *shell)
{
	char	*cmd_path;

	cmd_path = get_cmd_path(cmd->args[0], shell->env);
	if (!cmd_path)
	{
		ft_putstr_fd(cmd->args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		free_cmd_node(cmd);
		free_tab((void **)shell->pipefd, shell->n_pipes + 1, 0);
		exit(127);
	}
	execve(cmd_path, cmd->args, shell->env);
	perror("execve");
	free(cmd_path);
	free_cmd_node(cmd);
	free_tab((void **)shell->pipefd, shell->n_pipes + 1, 0);
	exit(EXIT_FAILURE);
}
