/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 12:14:55 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/25 12:18:44 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	**ft_dup_array(char **args)
{
	int		i;
	char	**result;

	i = 0;
	while (args[i])
		i++;
	result = (char **)malloc(sizeof(char *) * (i + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (args[i])
	{
		result[i] = ft_strdup(args[i]);
		if (!result[i])
		{
			free_tab((void **)result, 0, 1);
			return (NULL);
		}
		i++;
	}
	result[i] = NULL;
	return (result);
}
