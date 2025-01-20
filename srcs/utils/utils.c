/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 11:15:56 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/21 00:06:12 by ltheveni         ###   ########.fr       */
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

long long	ft_atoi_exit(const char *str, int *overflow)
{
	long long	result;
	int			sign;
	int			i;

	sign = 1;
	result = 0;
	i = 0;
	*overflow = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i++] == '-')
			sign *= -1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (result > (LLONG_MAX - (str[i] - '0')) / 10)
		{
			*overflow = 1;
			return (0);
		}
		result = result * 10 + (str[i++] - '0');
	}
	return (result * sign);
}
