/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_spaces_on_operator.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 12:56:38 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/26 19:11:54 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	handle_operator_size(const char *input, int *i, int *count)
{
	if ((input[*i + 1] == '>' && input[*i] == '>') || (input[*i + 1] == '<'
			&& input[*i + 1] == '<'))
	{
		if (*i > 0 && !ft_sp(input[*i - 1]))
			(*count)++;
		(*count) += 2;
		(*i)++;
		if (input[*i + 1] && !ft_sp(input[*i + 1]))
			(*count)++;
	}
	else
	{
		if (*i > 0 && !ft_sp(input[*i - 1]))
			(*count)++;
		(*count)++;
		if (input[*i + 1] && !ft_sp(input[*i + 1]))
			(*count)++;
	}
}

static int	size_with_spaces(const char *input)
{
	int		i;
	int		count;
	t_split	state;

	i = 0;
	count = 0;
	state = (t_split){0, 0, 0, 0};
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
			is_quote(input[i], &state);
		if ((input[i] == '>' || input[i] == '<') && !state.in_single_quote
			&& !state.in_double_quote)
			handle_operator_size(input, &i, &count);
		else
			count++;
		i++;
	}
	return (count);
}

static void	handle_operator(const char *input, int *i, int *j, char *result)
{
	if ((input[*i + 1] == '>' && input[*i] == '>') || (input[*i + 1] == '<'
			&& input[*i + 1] == '<'))
	{
		if (*i > 0 && !ft_sp(input[*i - 1]))
			result[(*j)++] = ' ';
		result[(*j)++] = input[(*i)++];
		result[(*j)++] = input[*i];
		if (input[*i + 1] && !ft_sp(input[*i + 1]))
			result[(*j)++] = ' ';
	}
	else
	{
		if (*i > 0 && !ft_sp(input[*i - 1]))
			result[(*j)++] = ' ';
		result[(*j)++] = input[*i];
		if (input[*i + 1] && !ft_sp(input[*i + 1]))
			result[(*j)++] = ' ';
	}
}

static void	spaces_loop(const char *input, char *result)
{
	int		i;
	int		j;
	t_split	state;

	i = 0;
	j = 0;
	state = (t_split){0, 0, 0, 0};
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
			is_quote(input[i], &state);
		if ((input[i] == '>' || input[i] == '<') && !state.in_single_quote
			&& !state.in_double_quote)
			handle_operator(input, &i, &j, result);
		else
			result[j++] = input[i];
		i++;
	}
	result[j] = '\0';
}

char	*add_spaces_on_operator(const char *input)
{
	char	*result;
	int		size;

	size = size_with_spaces(input);
	result = (char *)malloc(sizeof(char) * (size + 1));
	if (!result)
		return (NULL);
	spaces_loop(input, result);
	return (result);
}
