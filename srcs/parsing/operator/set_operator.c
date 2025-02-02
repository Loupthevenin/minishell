/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_operator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 09:33:53 by ltheveni          #+#    #+#             */
/*   Updated: 2025/02/02 11:20:47 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	add_redirect(t_cmd *cmd, char *file, int is_append, int is_input)
{
	t_redirects	*new_redir;
	t_redirects	*temp;

	new_redir = (t_redirects *)malloc(sizeof(t_redirects));
	if (!new_redir)
		return ;
	new_redir->infile = NULL;
	new_redir->outfile = NULL;
	new_redir->is_append = is_append;
	new_redir->is_here_doc = 0;
	new_redir->delimiter_here_doc = NULL;
	new_redir->next = NULL;
	if (is_input)
		new_redir->infile = file;
	else
		new_redir->outfile = file;
	if (!cmd->redirects)
		cmd->redirects = new_redir;
	else
	{
		temp = cmd->redirects;
		while (temp->next)
			temp = temp->next;
		temp->next = new_redir;
	}
}

void	assign_operator(t_cmd **current_node, char **args, int i)
{
	t_redirects	*last;

	if (!ft_strcmp(args[i], ">"))
		add_redirect((*current_node), rm_quotes(args[i + 1]), 0, 0);
	else if (!ft_strcmp(args[i], "<"))
		add_redirect((*current_node), rm_quotes(args[i + 1]), 0, 1);
	else if (!ft_strcmp(args[i], ">>"))
		add_redirect((*current_node), rm_quotes(args[i + 1]), 1, 0);
	else if (!ft_strcmp(args[i], "<<"))
	{
		add_redirect((*current_node), NULL, 0, 0);
		last = (*current_node)->redirects;
		while (last->next)
			last = last->next;
		if (args[i + 1] && args[i + 1][0] == '"' && args[i + 1][1] == '\0')
			last->delimiter_here_doc = ft_strdup("");
		else
			last->delimiter_here_doc = ft_strdup(args[i + 1]);
		last->is_here_doc = 1;
	}
}

void	set_operator(t_cmd **current_node)
{
	char	**args;
	int		i;

	i = 0;
	args = (*current_node)->args;
	while (args[i])
	{
		if (if_op(args[i]))
		{
			assign_operator(current_node, args, i);
			rm_element_tab((*current_node)->args, i);
			rm_element_tab((*current_node)->args, i);
		}
		else
			i++;
	}
}
