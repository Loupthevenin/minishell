/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:05:14 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/16 15:07:38 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// ici on cree une node;
t_cmd	*create_node(char **args)
{
	t_cmd	*new_node;

	new_node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_node)
		return (NULL);
	new_node->args = args;
	new_node->infile = NULL;
	new_node->outfile = NULL;
	new_node->next = NULL;
	return (new_node);
}

// ici on ajoute la nouvelle node a la fin de celle en tete;
void	append_node(t_cmd **head, t_cmd *new_node)
{
	t_cmd	*temp;

	if (!head || !new_node)
		return ;
	if (!*head)
	{
		*head = new_node;
		return ;
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = new_node;
}

// strlen de la linked list cmd;
int	get_command_count(t_cmd *head)
{
	t_cmd	*current;
	int		i;

	current = head;
	i = 0;
	while (current)
	{
		current = current->next;
		i++;
	}
	return (i);
}

// ici on free les nodes;
void	free_cmd_node(t_cmd *head)
{
	t_cmd	*temp;
	int		i;

	while (head)
	{
		temp = head;
		head = head->next;
		i = 0;
		if (temp->args)
		{
			while (temp->args[i])
			{
				free(temp->args[i]);
				i++;
			}
			free(temp->args);
		}
		if (temp->infile)
			free(temp->infile);
		if (temp->outfile)
			free(temp->outfile);
		free(temp);
	}
}
