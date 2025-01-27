/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 11:39:41 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/27 13:02:05 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle_error_process(t_cmd *cmd, t_shell *shell, char **envp,
		int exit_error)
{
	free_cmd_node(cmd);
	free_tab((void **)envp, 0, 1);
	free_shell(shell);
	exit(exit_error);
}

static void	handle_error_file(t_cmd *cmd, t_shell *shell, char **envp)
{
	if (ft_strchr(cmd->args[0], '/'))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->args[0], 2);
		ft_putendl_fd(": No such file or directory", 2);
		handle_error_process(cmd, shell, envp, 127);
	}
	ft_putstr_fd("minishell: command not found: ", 2);
	ft_putendl_fd(cmd->args[0], 2);
	handle_error_process(cmd, shell, envp, 127);
}

void	process(t_cmd *cmd, t_shell *shell)
{
	char	*cmd_path;
	char	**envp;

	if (is_builtins(cmd))
	{
		exec_builtins(shell, cmd);
		handle_error_process(cmd, shell, NULL, shell->last_exit);
	}
	envp = list_to_double_array(shell->env_list);
	if (!envp)
	{
		perror("minishell: failed alloc memory environment");
		handle_error_process(cmd, shell, envp, EXIT_FAILURE);
	}
	cmd_path = get_cmd_path(cmd->args[0], envp);
	if (!cmd_path)
		handle_error_file(cmd, shell, envp);
	execve(cmd_path, cmd->args, envp);
	perror("execve");
	free(cmd_path);
	handle_error_process(cmd, shell, envp, EXIT_FAILURE);
}
