/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 11:15:56 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/15 10:36:45 by ltheveni         ###   ########.fr       */
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

void	close_pipes(int **pipes, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}
