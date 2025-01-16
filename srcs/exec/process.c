/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 11:39:41 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/15 20:19:21 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle_error_process(t_cmd *cmd, t_shell *shell, char **envp,
		int exit_error)
{
	(void)shell;
	free_cmd_node(cmd);
	free_tab((void **)envp, 0, 1);
	exit(exit_error);
}

void	process(t_cmd *cmd, t_shell *shell)
{
	char	*cmd_path;
	char	**envp;

	envp = list_to_double_array(shell->env_list);
	if (!envp)
	{
		perror("minishell: failed alloc memory environment");
		free_cmd_node(cmd);
		exit(EXIT_FAILURE);
	}
	cmd_path = get_cmd_path(cmd->args[0], envp);
	if (!cmd_path)
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putendl_fd(cmd->args[0], 2);
		handle_error_process(cmd, shell, envp, 127);
	}
	execve(cmd_path, cmd->args, envp);
	perror("execve");
	free(cmd_path);
	handle_error_process(cmd, shell, envp, EXIT_FAILURE);
}
