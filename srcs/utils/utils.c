/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 11:15:56 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/17 08:31:51 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_tab(void **tabs, int size, int is_null)
{
	int	i;

	if (!tabs)
		return ;
	i = 0;
	if (is_null)
	{
		while (tabs[i])
		{
			free(tabs[i]);
			i++;
		}
	}
	else
	{
		while (i < size)
		{
			free(tabs[i]);
			i++;
		}
	}
	free(tabs);
}

static void	free_env_node(t_env *head)
{
	t_env	*temp;

	while (head)
	{
		temp = head;
		head = head->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
}

void	free_shell(t_shell *shell)
{
	if (!shell)
		return ;
	if (shell->env_list)
		free_env_node(shell->env_list);
	shell->env_list = NULL;
}

char	*get_value_env(t_env *env, const char *key)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (!ft_strcmp(current->key, key))
			return (current->value);
		current = current->next;
	}
	return (NULL);
}
