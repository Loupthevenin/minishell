/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_operator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 09:33:53 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/27 17:48:10 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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
			if (!save || !ft_strcmp(save, args[i]))
				count++;
			save = args[i];
		}
		i++;
	}
	return (count);
}

void	assign_operator(t_cmd **current_node, char **args, int op_index)
{
	if (!ft_strcmp(args[op_index], ">"))
	{
		(*current_node)->outfile = remove_s_quotes(args[op_index + 1]);
	}
	else if (!ft_strcmp(args[op_index], "<"))
	{
		(*current_node)->infile = remove_s_quotes(args[op_index + 1]);
	}
	else if (!ft_strcmp(args[op_index], ">>"))
	{
		(*current_node)->outfile = remove_s_quotes(args[op_index + 1]);
		(*current_node)->is_append = 1;
	}
	else if (!ft_strcmp(args[op_index], "<<"))
	{
		if (args[op_index + 1] && args[op_index + 1][0] == '"' && args[op_index
			+ 1][1] == '\0')
			(*current_node)->delimiter_here_doc = ft_strdup("");
		else
			(*current_node)->delimiter_here_doc = remove_s_quotes(args[op_index
					+ 1]);
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
			assign_operator(current_node, args, i);
			rm_element_tab((*current_node)->args, i);
			rm_element_tab((*current_node)->args, i);
		}
		else
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
		multiple_operator(current_node, count);
}
