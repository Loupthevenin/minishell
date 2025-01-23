/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0-parser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kleung-t <kleung-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 14:02:48 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/23 17:28:11 by kleung-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//	malloc_word_arg | parse_input

// 1 = OP, 2 = TOKEN
char	*malloc_word_arg(const char *s, int delimiter_type)
{
	int		i;
	char	*word;

	i = 0;
	while (s[i] && ((delimiter_type == 1 && !if_op(s))
			|| (delimiter_type == 2 && !ft_sp(s[i]))))
		i++;
	word = (char *)malloc(sizeof(char) * (i + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (s[i] && ((delimiter_type == 1 && !if_op(s))
			|| (delimiter_type == 2 && !ft_sp(s[i]))))
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
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
	int		i;
	char	**tmp;
	t_cmd	*head;
	t_cmd	*new_node;

	i = 0;
	tmp = split_input(input);
	if (!tmp)
		return (NULL);
	head = NULL;
	tmp = (char **)malloc(sizeof(char *) * ((count_op(input)) + 1));
	tmp[count_op(input) + 1] = 0;
	tmp = create_tab(input, tmp);
	while (tmp[i])
	{
		new_node = create_node(split_arg(tmp[i]));
		if (!new_node)
		{
			free_cmd_node(head);
			free_tab((void **)new_node->args, 0, 1);
			return (NULL);
		}
		else if (i == 0)
			head = new_node;
		else
			append_node(&head, new_node);
		i++;
	}
	print_node(head);
	free_tab((void **)new_node->args, 0, 1);
	return (head);
}
