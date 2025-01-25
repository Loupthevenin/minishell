/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0-parser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kleung-t <kleung-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 14:02:48 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/25 11:26:07 by ltheveni         ###   ########.fr       */
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
		printf("token %d infile : [%s]\n", i, current->infile);
		printf("token %d outfile : [%s]\n", i, current->outfile);
		printf("token %d here_doc_delimiter : [%s]\n", i,
				current->delimiter_here_doc);
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
		set_operator(&new_node);
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
	char	*with_spaces;
	t_cmd	*head;

	head = NULL;
	// A IMPLEMENTER CHECK TOUT LES CAS DU DEBUT DU TABLEAU XLSX;
	/* check_input(input, shell); */
	formatted = format_input(input, shell);
	if (!formatted)
		return (NULL);
	with_spaces = add_spaces_on_operator(formatted);
	free(formatted);
	if (!with_spaces)
		return (NULL);
	printf("%s\n", with_spaces);
	tmp = split_input(with_spaces);
	free(with_spaces);
	print_tab(tmp);
	if (!tmp)
		return (NULL);
	if (!loop_parse_input(tmp, &head))
		return (NULL);
	print_node(head);
	free_tab((void **)tmp, 0, 1);
	return (head);
}
