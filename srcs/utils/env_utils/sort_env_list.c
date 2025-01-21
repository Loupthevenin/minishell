/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:47:20 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/21 16:03:42 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	selection_sort_env(char **array, int size)
{
	int		i;
	int		j;
	int		min;
	char	*temp;

	i = 0;
	while (i < size)
	{
		min = i;
		j = i + 1;
		while (j < size)
		{
			if (ft_strcmp(array[j], array[min]) < 0)
				min = j;
			j++;
		}
		if (min != i)
		{
			temp = array[i];
			array[i] = array[min];
			array[min] = temp;
		}
		i++;
	}
}
