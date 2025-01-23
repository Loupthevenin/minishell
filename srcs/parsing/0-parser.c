/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0-parser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kleung-t <kleung-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 14:02:48 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/23 22:48:07 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

// affiche une tab;
static void	print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("tab :%d %s\n", i, tab[i]);
		i++;
	}
}

static int	loop_parse_input(char **tmp, t_cmd **head)
{
	int		i;
	t_cmd	*new_node;

	i = 0;
	while (tmp[i])
	{
		new_node = create_node(split_arg(tmp[i]));
		if (!new_node)
		{
			free_cmd_node(*head);
			free_tab((void **)tmp, 0, 1);
			return (0);
		}
		if (i == 0)
			*head = new_node;
		else
			append_node(head, new_node);
		i++;
	}
	return (1);
}

t_cmd	*parse_input(const char *input, t_shell *shell)
{
	char	**tmp;
	char	*formatted;
	t_cmd	*head;

	head = NULL;
	formatted = format_input(input, shell);
	if (!formatted)
		return (NULL);
	printf("%s\n", formatted);
	tmp = split_input(formatted);
	print_tab(tmp);
	free(formatted);
	if (!tmp)
		return (NULL);
	if (!loop_parse_input(tmp, &head))
		return (NULL);
	print_node(head);
	free_tab((void **)tmp, 0, 1);
	return (head);
}
