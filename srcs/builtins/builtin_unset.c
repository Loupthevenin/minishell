/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:49:38 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/21 11:45:43 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_identifier(char *s)
{
	int	i;

	if (!s || (!ft_isalpha(s[0]) && s[0] != '_'))
		return (0);
	i = 0;
	while (s[i])
	{
		if (!ft_isalpha(s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	unset_env_var(t_env **env, const char *key)
{
	t_env	*current;
	t_env	*prev;

	if (!env || !*env || !key)
		return ;
	current = *env;
	prev = NULL;
	while (current)
	{
		if (!ft_strcmp(current->key, key))
		{
			if (!prev)
				*env = current->next;
			else
				prev->next = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

void	builtin_unset(t_shell *shell, t_cmd *cmd)
{
	int	i;

	if (!cmd->args[1])
	{
		shell->last_exit = 0;
		return ;
	}
	i = 1;
	while (cmd->args[i])
	{
		if (!check_identifier(cmd->args[i]))
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(cmd->args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			shell->last_exit = EXIT_FAILURE;
		}
		else
			unset_env_var(&shell->env_list, cmd->args[i]);
		i++;
	}
	shell->last_exit = 0;
}
