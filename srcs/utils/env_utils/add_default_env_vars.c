/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_default_env_vars.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 19:47:42 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/25 19:58:11 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static t_env	*create_env_node(char *key, char *value)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(key);
	if (value)
		new_node->value = ft_strdup(value);
	else
		new_node->value = NULL;
	new_node->next = NULL;
	return (new_node);
}

static void	add_env_node(t_env **env, t_env *new_node)
{
	t_env	*current;

	if (!env || !new_node)
		return ;
	if (!*env)
	{
		*env = new_node;
		return ;
	}
	current = *env;
	while (current->next)
		current = current->next;
	current->next = new_node;
}

void	add_default_env_vars(t_env **env)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		perror("getcwd failed");
		pwd = ft_strdup("/");
	}
	add_env_node(env, create_env_node("PWD", pwd));
	free(pwd);
	add_env_node(env, create_env_node("SHLVL", "1"));
	add_env_node(env, create_env_node("_", "/usr/bin/env"));
	add_env_node(env, create_env_node("OLDPWD", NULL));
}
