/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 18:07:41 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/29 10:37:38 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_parent_builtins(t_cmd *cmd)
{
	if (!cmd->args[0])
		return (0);
	if (!ft_strcmp(cmd->args[0], "cd"))
		return (1);
	else if (!ft_strcmp(cmd->args[0], "exit"))
		return (1);
	else if (!ft_strcmp(cmd->args[0], "export"))
		return (1);
	else if (!ft_strcmp(cmd->args[0], "unset"))
		return (1);
	return (0);
}

int	is_builtins(t_cmd *cmd)
{
	if (!cmd->args[0])
		return (0);
	if (!ft_strcmp(cmd->args[0], "echo"))
		return (1);
	else if (!ft_strcmp(cmd->args[0], "cd"))
		return (1);
	else if (!ft_strcmp(cmd->args[0], "pwd"))
		return (1);
	else if (!ft_strcmp(cmd->args[0], "export"))
		return (1);
	else if (!ft_strcmp(cmd->args[0], "unset"))
		return (1);
	else if (!ft_strcmp(cmd->args[0], "env"))
		return (1);
	else if (!ft_strcmp(cmd->args[0], "exit"))
		return (1);
	return (0);
}

void	exec_builtins(t_shell *shell, t_cmd *cmd)
{
	if (!ft_strcmp(cmd->args[0], "echo"))
		builtin_echo(shell, cmd);
	else if (!ft_strcmp(cmd->args[0], "cd"))
		builtin_cd(shell, cmd);
	else if (!ft_strcmp(cmd->args[0], "pwd"))
		builtin_pwd(shell, cmd);
	else if (!ft_strcmp(cmd->args[0], "export"))
		builtin_export(shell, cmd);
	else if (!ft_strcmp(cmd->args[0], "unset"))
		builtin_unset(shell, cmd);
	else if (!ft_strcmp(cmd->args[0], "env"))
		builtin_env(shell, cmd);
	else if (!ft_strcmp(cmd->args[0], "exit"))
		builtin_exit(shell, cmd);
}
