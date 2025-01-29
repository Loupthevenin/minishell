/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_parser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kleung-t <kleung-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 14:02:48 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/29 15:16:53 by ltheveni         ###   ########.fr       */
/*   Updated: 2025/01/27 17:49:35 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		remove_quotes(&new_node);
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
	formatted = format_input(input, shell);
	if (!formatted)
		return (NULL);
	with_spaces = add_spaces_on_operator(formatted);
	free(formatted);
	if (!with_spaces)
		return (NULL);
	tmp = split_input(with_spaces);
	free(with_spaces);
	if (!tmp)
		return (NULL);
	if (!loop_parse_input(tmp, &head))
		return (NULL);
	free_tab((void **)tmp, 0, 1);
	return (head);
}
