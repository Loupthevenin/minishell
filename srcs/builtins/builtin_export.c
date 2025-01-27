/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:50:28 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/27 11:59:22 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_export(t_env *env)
{
	char	**sorted_copy;
	int		size;
	int		i;

	sorted_copy = list_to_double_array(env);
	if (!sorted_copy)
		return ;
	size = get_size_env(env);
	selection_sort_env(sorted_copy, size);
	i = 0;
	while (i < size)
	{
		if (ft_strncmp(sorted_copy[i], "_=", 2))
			printf("declare -x %s\n", sorted_copy[i]);
		i++;
	}
	free_tab((void **)sorted_copy, 0, 1);
}

void	update_env_var(t_env *env, char *key, char *new_value)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (!ft_strcmp(current->key, key))
		{
			free(current->value);
			current->value = ft_strdup(new_value);
			return ;
		}
		current = current->next;
	}
}

static void	add_env_var(t_env **env, char *key, char *value)
{
	t_env	*new_var;

	if (!key || !*key)
	{
		ft_putstr_fd("Error: Invalid key", 2);
		return ;
	}
	new_var = malloc(sizeof(t_env));
	if (!new_var)
	{
		return ;
	}
	new_var->key = ft_strdup(key);
	if (value)
		new_var->value = ft_strdup(value);
	else
		new_var->value = NULL;
	new_var->next = *env;
	*env = new_var;
}

static void	update_value(t_env **env, char *args)
{
	char	*equal_sign;
	char	*key;
	char	*value;

	equal_sign = ft_strchr(args, '=');
	key = NULL;
	value = NULL;
	if (equal_sign)
	{
		key = ft_strndup(args, equal_sign - args);
		value = ft_strdup(equal_sign + 1);
		if (get_value_env(*env, key))
			update_env_var(*env, key, value);
		else
			add_env_var(env, key, value);
		free(value);
	}
	else
	{
		key = ft_strdup(args);
		add_env_var(env, key, NULL);
	}
	free(key);
}

void	builtin_export(t_shell *shell, t_cmd *cmd)
{
	int	i;

	if (!cmd->args[1])
	{
		print_export(shell->env_list);
		shell->last_exit = 0;
		return ;
	}
	i = 1;
	while (cmd->args[i])
	{
		if (!check_identifier_export(cmd->args[i]))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(cmd->args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			shell->last_exit = EXIT_FAILURE;
			return ;
		}
		else
			update_value(&shell->env_list, cmd->args[i]);
		i++;
	}
	shell->last_exit = 0;
}
