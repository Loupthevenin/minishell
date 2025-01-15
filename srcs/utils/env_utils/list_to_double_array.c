/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_double_array.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:50:30 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/15 15:30:57 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	env_list_size(t_env *env)
{
	int		i;
	t_env	*current;

	i = 0;
	current = env;
	while (current)
	{
		current = current->next;
		i++;
	}
	return (i);
}

static char	**loop_list_to_double_array(char **result, t_env *env, int len_list)
{
	int		i;
	t_env	*current;
	size_t	len_string;

	i = 0;
	current = env;
	while (i < len_list)
	{
		len_string = ft_strlen(current->key) + ft_strlen(current->value) + 2;
		result[i] = (char *)malloc(sizeof(char) * (len_string));
		if (!result[i])
		{
			free_tab((void **)result, 0, 1);
			return (NULL);
		}
		ft_strlcpy(result[i], current->key, ft_strlen(current->key) + 1);
		ft_strlcat(result[i], "=", len_string);
		ft_strlcat(result[i], current->value, len_string);
		i++;
		current = current->next;
	}
	result[i] = NULL;
	return (result);
}

char	**list_to_double_array(t_env *env)
{
	char	**result;
	int		len_list;

	len_list = env_list_size(env);
	result = (char **)malloc(sizeof(char *) * (len_list + 1));
	if (!result)
		return (NULL);
	return (loop_list_to_double_array(result, env, len_list));
}
