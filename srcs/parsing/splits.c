/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splits.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 09:52:09 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/14 10:55:10 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// return 1 if identical
static int	ft_sp(char c)
{
	if ((c >= 7 && c <= 13) || c == 32 || c == 0)
		return (1);
	else
		return (0);
}

static char	*malloc_word(char const *s, int delimiter_type)
{
	int		i;
	char	*word;

	i = 0;
	while (s[i] && ((delimiter_type == 1 && !ft_op(&s[i]))
			|| (delimiter_type == 2 && !ft_sp(s[i]))))
		i++;
	word = (char *)malloc(sizeof(char) * (i + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (s[i] && ((delimiter_type == 1 && !ft_op(&s[i]))
			|| (delimiter_type == 2 && !ft_sp(s[i]))))
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

// 1 = OP, 2 = TOKEN
static int	count_world(char const *arg, int code)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (arg[i])
	{
		if ((code == 1 && ft_op(&arg[i])) || (code == 2 && !ft_sp(arg[i])))
		{
			count++;
			while (arg[i] && ((code == 1 && ft_op(&arg[i])) || (code == 2
						&& !ft_sp(arg[i]))))
				i++;
		}
		else
			i++;
	}
	return (count);
}

char	**split_input(char const *s)
{
	int		i;
	char	**result;

	if (!s)
		return (NULL);
	result = (char **)malloc(sizeof(char *) * (count_world(s, 1) + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s && ft_op(s))
			s++;
		if (*s)
		{
			result[i] = malloc_word(s, 1);
			if (!result)
				return (free_tab((void **)result, i, 0), NULL);
			i++;
			while (*s && !ft_op(s))
				s++;
		}
	}
	result[i] = NULL;
	return (result);
}

char	**split_arg(char const *s)
{
	int		i;
	char	**result;

	if (!s)
		return (NULL);
	result = (char **)malloc(sizeof(char *) * (count_world(s, 2) + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s && ft_sp(*s))
			s++;
		if (*s)
		{
			result[i] = malloc_word(s, 2);
			if (!result)
				return (free_tab((void **)result, i, 0), NULL);
			i++;
			while (*s && !ft_sp(*s))
				s++;
		}
	}
	result[i] = NULL;
	return (result);
}
