/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 14:06:28 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/09 17:45:02 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	wait_for_children(t_cmd *cmd)
{
	t_cmd	*current;

	current = cmd;
	while (current)
	{
		wait(NULL);
		current = current->next;
	}
}

void	exec_cmd(t_cmd *cmd, char **envp)
{
	fork_processes(cmd, envp);
	wait_for_children(cmd);
}
