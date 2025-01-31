/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:53:55 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/31 14:57:16 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_error_process(t_cmd *cmd, t_shell *shell, char **envp,
		int exit_error)
{
	free_cmd_node(cmd);
	free_tab((void **)envp, 0, 1);
	free_shell(shell);
	exit(exit_error);
}

void	handle_error_file(t_cmd *cmd, t_shell *shell, char **envp)
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

void	handle_error_execve(t_cmd *cmd, t_shell *shell, char **envp,
		int exit_error)
{
	if (exit_error == 126)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->args[0], 2);
		ft_putendl_fd(": Permission denied", 2);
		handle_error_process(cmd, shell, envp, exit_error);
	}
	else if (exit_error == 127)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->args[0], 2);
		ft_putendl_fd(": No such file or directory", 2);
		handle_error_process(cmd, shell, envp, exit_error);
	}
}
