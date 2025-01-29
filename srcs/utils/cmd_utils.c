/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kleung-t <kleung-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:05:14 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/29 15:32:25 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*create_node(char **arg)
{
	t_cmd	*new_node;

	new_node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_node)
		return (NULL);
	new_node->args = arg;
	new_node->redirects = NULL;
	new_node->next = NULL;
	return (new_node);
}

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

void	free_redirects(t_redirects *head)
{
	t_redirects	*temp;

	while (head)
	{
		temp = head;
		head = head->next;
		if (temp->infile)
			free(temp->infile);
		if (temp->outfile)
			free(temp->outfile);
		if (temp->delimiter_here_doc)
			free(temp->delimiter_here_doc);
		free(temp);
	}
}

void	free_cmd_node(t_cmd *head)
{
	t_cmd	*temp;
	int		i;

	while (head)
	{
		temp = head;
		head = head->next;
		if (temp->args)
		{
			i = 0;
			while (temp->args[i])
			{
				free(temp->args[i]);
				i++;
			}
			free(temp->args);
		}
		if (temp->redirects)
			free_redirects(temp->redirects);
		free(temp);
	}
}
