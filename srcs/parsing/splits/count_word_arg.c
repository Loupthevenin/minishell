/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_word_arg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 14:58:26 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/26 15:04:16 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	handle_loop_arg(const char *arg, int *i, int *count, t_split *state)
{
	is_quote(arg[*i], state);
	(*count)++;
	(*i)++;
	while (arg[*i] && ((state->in_single_quote && arg[*i] != '\'')
			|| (state->in_double_quote && arg[*i] != '"')))
		(*i)++;
	if (arg[*i] == '\'' || arg[*i] == '"')
		is_quote(arg[*i], state);
	(*i)++;
}

int	count_word_arg(const char *arg)
{
	int		i;
	int		count;
	t_split	state;

	state = (t_split){0, 0, 0, 0};
	i = 0;
	count = 0;
	while (arg[i])
	{
		if ((arg[i] == '\'' || arg[i] == '"') && !state.in_single_quote
			&& !state.in_double_quote)
			handle_loop_arg(arg, &i, &count, &state);
		else if (ft_sp(arg[i]))
		{
			while (arg[i] && ft_sp(arg[i]))
				i++;
		}
		else
		{
			count++;
			while (arg[i] && !ft_sp(arg[i]) && arg[i] != '\'' && arg[i] != '"')
				i++;
		}
	}
	return (count);
}
