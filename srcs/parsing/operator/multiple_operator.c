/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_operator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 15:53:50 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/25 16:40:23 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	remove_operator_file(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (if_op(args[i]))
		{
			rm_element_tab(args, i);
			if (args[i])
				rm_element_tab(args, i);
		}
		else
			i++;
	}
}

static int	find_operator(char **args, int n)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (args[i])
	{
		if (if_op(args[i]))
		{
			if (count == n)
				return (i);
			count++;
		}
		i++;
	}
	return (-1);
}

static void	handle_error_mult_operator(char **args, char **true_args)
{
	free_tab((void **)args, 0, 1);
	free_tab((void **)true_args, 0, 1);
	return ;
}

static void	multiple_operator_loop(t_cmd **current_node, int count, char **args,
		char **true_args)
{
	int		i;
	int		op_index;
	t_cmd	*new_node;

	i = 0;
	op_index = 0;
	new_node = NULL;
	while (i < count)
	{
		op_index = find_operator(args, i);
		if (i++ == 0)
		{
			free_tab((void **)(*current_node)->args, 0, 1);
			(*current_node)->args = ft_dup_array(true_args);
			assign_operator(current_node, args, op_index);
		}
		else
		{
			new_node = create_node(ft_dup_array(true_args));
			if (!new_node)
				return (handle_error_mult_operator(args, true_args));
			assign_operator(&new_node, args, op_index);
			append_node(current_node, new_node);
		}
	}
}

void	multiple_operator(t_cmd **current_node, int count)
{
	char	**args;
	char	**true_args;

	args = ft_dup_array((*current_node)->args);
	true_args = ft_dup_array((*current_node)->args);
	remove_operator_file(true_args);
	multiple_operator_loop(current_node, count, args, true_args);
	free_tab((void **)args, 0, 1);
	free_tab((void **)true_args, 0, 1);
}
