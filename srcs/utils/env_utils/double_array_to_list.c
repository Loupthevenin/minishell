/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_array_to_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 11:28:44 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/15 14:51:24 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static t_env	*create_env_node(char *key, char *value)
{
	t_env	*current;

	current = (t_env *)malloc(sizeof(t_env));
	if (!current)
		return (NULL);
	current->key = key;
	current->value = value;
	current->next = NULL;
	return (current);
}

static void	append_env_node(t_env **head, t_env *new_node)
{
	if (!head || !new_node)
		return ;
	new_node->next = *head;
	*head = new_node;
}

static t_env	*parse_env(char *s)
{
	char	*sep;
	char	*key;
	char	*value;

	sep = ft_strchr(s, '=');
	if (!sep)
		return (NULL);
	key = ft_strndup(s, sep - s);
	if (!key)
		return (NULL);
	value = ft_strdup(sep + 1);
	if (!value)
		return (NULL);
	return (create_env_node(key, value));
}

t_env	*double_array_to_list(char **envp)
{
	t_env	*head;
	t_env	*new_node;
	int		i;

	i = 0;
	head = NULL;
	while (envp[i])
	{
		new_node = parse_env(envp[i]);
		if (new_node)
			append_env_node(&head, new_node);
		i++;
	}
	return (head);
}
