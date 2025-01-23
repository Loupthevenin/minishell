/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0-parser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kleung-t <kleung-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 14:02:48 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/23 16:38:20 by kleung-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//	parse_input

// affiche les args;
static void	print_node(t_cmd *head)
{
	int		i;
	int		j;
	t_cmd	*current;

	i = 0;
	current = head;
	while (current)
	{
		j = 0;
		while (current->args[j])
			printf("token %d : [%s]\n", i, current->args[j++]);
		current = current->next;
		i++;
	}
}

t_cmd	*parse_input(const char *input)
{
	t_cmd	*cmd;
	int		i;
	int		j;
	char	**tmp;
	t_cmd	*head;
	t_cmd	*new_node;

	i = 0;
	j = 0;
	tmp = split_input(input);
	if (!tmp)
		return (NULL);
	head = NULL;
	tmp = (char **)malloc(sizeof(char *) * ((count_op(s)) + 1));
	tmp[count_op(s) + 1]  = 0;
	tmp = create_tab( input, tmp);
	while (tmp[i])
	{
		new_node = create_node(split_arg(tmp[i]));
		if (!new_node)
		{
			free_cmd_node(head);
			free_tab((void **)cmd->args, 0, 1);
			return (NULL);
		}
		else if (i == 0)
			head = new_node;
		else
			append_node(&head, new_node);
		i++;
	}
	print_node(head);
	free_tab((void **)cmd->args, 0, 1);
	return (head);
}
