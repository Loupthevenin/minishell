/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kleung-t <kleung-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 14:02:48 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/15 09:33:23 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// returns 1 if identical
int	ft_op(const char *s)
{
	if (!s || !*s)
		return (0);
	if (!strncmp(s, "<<", 2) || !strncmp(s, ">>", 2))
		return (1);
	if (*s == '|' || *s == '<' || *s == '>')
		return (1);
	return (0);
}

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

t_cmd	*parse_input(char *input)
{
	int		i;
	char	**args;
	t_cmd	*head;
	t_cmd	*new_node;

	i = 0;
	args = ft_split(input, '|');
	if (!args)
		return (NULL);
	head = NULL;
	while (args[i])
	{
		// ici changer le split par le split qui vire les isspaces
		new_node = create_node(ft_split(args[i++], ' '));
		if (!new_node)
		{
			free_cmd_node(head);
			free_tab((void **)args, 0, 1);
			return (NULL);
		}
		if (i == 0)
			head = new_node;
		else
			append_node(&head, new_node);
	}
	print_node(head);
	free_tab((void **)args, 0, 1);
	return (head);
}
