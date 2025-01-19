/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kleung-t <kleung-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 14:02:48 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/19 17:48:35 by kleung-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// returns 1 if identical
int	if_op_char(const char *s, int i)
{
	if (!s)
		return (0);
	if (s[i] == '|' || s[i] == '<' || s[i] == '>')
		return (1);
	return (0);
}

// returns 1 if identical
int	if_op(const char *s)
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

t_cmd	*parse_input(const char *input)
{
	t_cmd	*cmd;
	int		i;
	char	**tmp;
	t_cmd	*head;
	t_cmd	*new_node;

	i = 0;
	tmp = split_input(input);
	if (!tmp)
		return (NULL);
	head = NULL;
	cmd = malloc(sizeof(t_cmd));
	cmd->args = NULL;
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
