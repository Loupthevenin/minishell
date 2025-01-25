/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_operator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 09:33:53 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/25 12:20:12 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_operator(char **args)
{
	int		i;
	int		count;
	char	*save;

	i = 0;
	count = 0;
	save = NULL;
	while (args[i])
	{
		if (if_op(args[i]))
		{
			if (save && !ft_strcmp(save, args[i]))
				count++;
			else
				count = 1;
			save = args[i];
		}
		i++;
	}
	return (count);
}

static void	assign_operator(t_cmd **current_node, int i)
{
	char	**args;

	args = (*current_node)->args;
	if (!ft_strcmp(args[i], ">"))
	{
		(*current_node)->outfile = ft_strdup(args[i + 1]);
	}
	else if (!ft_strcmp(args[i], "<"))
	{
		(*current_node)->infile = ft_strdup(args[i + 1]);
	}
	else if (!ft_strcmp(args[i], ">>"))
	{
		(*current_node)->outfile = ft_strdup(args[i + 1]);
		(*current_node)->is_append = 1;
	}
	else if (!ft_strcmp(args[i], "<<"))
	{
		(*current_node)->delimiter_here_doc = ft_strdup(args[i + 1]);
		(*current_node)->is_here_doc = 1;
	}
}

static void	one_operator(t_cmd **current_node)
{
	char	**args;
	int		i;

	i = 0;
	args = (*current_node)->args;
	while (args[i])
	{
		if (if_op(args[i]))
		{
			assign_operator(current_node, i);
			rm_element_tab((*current_node)->args, i);
			rm_element_tab((*current_node)->args, i);
		}
		i++;
	}
}

static void	multiple_operator(t_cmd **current_node)
{
	char	**args;
	int		i;
	int		count;
	t_cmd	*new_node;

	new_node = NULL;
	i = 0;
	count = 0;
	args = (*current_node)->args;
	while (args[i])
	{
		if (if_op(args[i]))
		{
			if (count == 0)
			{
				assign_operator(current_node, i);
				rm_element_tab((*current_node)->args, i);
				rm_element_tab((*current_node)->args, i);
			}
			else
			{
				new_node = create_node(ft_dup_array((*current_node)->args));
				if (!new_node)
					return ;
				assign_operator(&new_node, i);
				rm_element_tab(new_node->args, i);
				rm_element_tab(new_node->args, i);
				append_node(current_node, new_node);
			}
			count++;
		}
		i++;
	}
}

void	set_operator(t_cmd **current_node)
{
	int	count;

	count = count_operator((*current_node)->args);
	if (count == 0)
		return ;
	if (count == 1)
		one_operator(current_node);
	else
		multiple_operator(current_node);
}
