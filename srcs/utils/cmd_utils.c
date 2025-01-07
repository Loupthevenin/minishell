/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:05:14 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/07 16:00:16 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_cmd_node(t_cmd *head)
{
	t_cmd	*temp;
	int		i;

	while (head)
	{
		temp = head;
		head = head->next;
		i = 0;
		while (temp->args[i])
			free(temp->args[i]);
		free(temp->args);
		if (temp->infile)
			free(temp->infile);
		if (temp->outfile)
			free(temp->outfile);
		if (temp->append)
			free(temp->append);
		free(temp);
	}
}
