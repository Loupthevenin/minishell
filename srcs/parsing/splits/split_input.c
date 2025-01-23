/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kleung-t <kleung-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 09:52:09 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/23 22:24:53 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	count_word_input(const char *arg)
{
	int		i;
	int		count;
	t_split	state;

	state = (t_split){0, 0, 0, 0};
	i = 0;
	count = 0;
	while (arg[i])
	{
		if (arg[i] == '\'' || arg[i] == '"')
			is_quote(arg[i], &state);
		if ((i == 0 || arg[i - 1] == '|') && !state.in_single_quote
			&& !state.in_double_quote)
			count++;
		i++;
	}
	return (count);
}

static int	extract_word(const char *s, char **result, t_split *state, int i)
{
	result[state->index] = (char *)malloc(i - state->start + 1);
	if (!result[state->index])
		return (0);
	ft_strlcpy(result[state->index], &s[state->start], i - state->start + 1);
	state->index++;
	return (1);
}

static int	process_split_input(const char *s, char **result, t_split *state)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
			is_quote(s[i], state);
		if (s[i] == '|' && !state->in_single_quote && !state->in_double_quote)
		{
			result[state->index] = (char *)malloc(i - state->start + 1);
			if (!result[state->index])
				return (free_tab((void **)result, 0, 1), 0);
			ft_strlcpy(result[state->index], &s[state->start], i - state->start
				+ 1);
			state->index++;
			state->start = i + 1;
		}
		i++;
	}
	if (state->start < i)
		if (!extract_word(s, result, state, i))
			return (free_tab((void **)result, 0, 1), 0);
	return (1);
}

// split on pipe
char	**split_input(const char *s)
{
	char	**result;
	t_split	state;

	if (!s)
		return (NULL);
	result = (char **)malloc(sizeof(char *) * (count_word_input(s) + 1));
	if (!result)
		return (NULL);
	state = (t_split){0, 0, 0, 0};
	if (!process_split_input(s, result, &state))
		return (NULL);
	result[state.index] = NULL;
	return (result);
}
