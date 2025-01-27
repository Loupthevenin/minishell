/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:46:20 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/27 12:10:57 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	*handle_error_target(t_shell *shell, char *key)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(key, 2);
	ft_putendl_fd(" not set", 2);
	shell->last_exit = EXIT_FAILURE;
	return (NULL);
}

static void	handle_error_cd(t_shell *shell, char *message)
{
	perror(message);
	shell->last_exit = EXIT_FAILURE;
	return ;
}

static char	*set_target(t_shell *shell, t_cmd *cmd)
{
	char	*target;

	if (!cmd->args[1])
	{
		target = get_value_env(shell->env_list, "HOME");
		if (!target)
			return (handle_error_target(shell, "HOME"));
	}
	else if (!ft_strcmp(cmd->args[1], "-"))
	{
		target = get_value_env(shell->env_list, "OLDPWD");
		if (!target)
			return (handle_error_target(shell, "OLDPWD"));
		printf("%s\n", target);
	}
	else if (cmd->args[1] && cmd->args[2])
	{
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		shell->last_exit = EXIT_FAILURE;
		return (NULL);
	}
	else
		target = cmd->args[1];
	return (target);
}

static void	update_env_values(t_env *env, char *old_pwd, char *new_pwd)
{
	update_env_var(env, "OLDPWD", old_pwd);
	update_env_var(env, "PWD", new_pwd);
}

void	builtin_cd(t_shell *shell, t_cmd *cmd)
{
	char	*target;
	char	*old_pwd;
	char	*new_pwd;

	target = set_target(shell, cmd);
	if (!target)
		return ;
	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		return (handle_error_cd(shell, "minishell: cd: getcwd"));
	if (chdir(target) != 0)
	{
		handle_error_cd(shell, "minishell: cd");
		return (free(old_pwd));
	}
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
	{
		handle_error_cd(shell, "minishell: cd: getcwd");
		return (free(old_pwd));
	}
	update_env_values(shell->env_list, old_pwd, new_pwd);
	free(old_pwd);
	free(new_pwd);
	shell->last_exit = 0;
}
