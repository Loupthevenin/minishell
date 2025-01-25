/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_element_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 09:22:05 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/25 09:30:30 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	rm_element_tab(char **tab, int index_remove)
{
	int	i;
	int	j;

	if (!tab || index_remove < 0)
		return ;
	i = 0;
	while (tab[i])
		i++;
	if (index_remove >= i)
		return ;
	free(tab[index_remove]);
	j = index_remove;
	while (j < i - 1)
	{
		tab[j] = tab[j + 1];
		j++;
	}
	tab[i - 1] = NULL;
}
