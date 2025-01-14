/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kleung-t <kleung-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 14:02:48 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/14 02:45:00 by kleung-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//t_cmd	*parse_input(char *input);

char	*malloc_word(char const *s, char c)
{
	int		i;
	char	*word;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	word = (char *)malloc(sizeof(char) * (i + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (s[i] != '\0' && s[i] != c)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

void	free_split(char **result, int words)
{
	int	i;

	i = 0;
	while (i < words)
	{
		free(result[i]);
		i++;
	}
	free(result);
}

//return 1 if identical
int	ft_sp(char c)
{
	if ((c >= 7 && c <= 13) || c == 32 || c == 0)
		return (1);
	else
		return (0);
}

//returns 1 if identical
int	ft_op(const char *s)
{
	if (!strcmp(s, "|"))
		return (1);
	else if (!strcmp(s, "<"))
		return (1);
	else if (!strcmp(s, ">"))
		return (1);
	else if (!strcmp(s, "<<"))
		return (1);
	else if (!strcmp(s, ">>"))
		return (1);
	else
		return (0);
}

int	count_world(char const *arg, int code)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	// 1 = OP, 2 = TOKEN
	if (code == 1)
	{
		if (ft_op(arg))
			count++;
		i++;
		return (count + 1);
	}
	if (code == 2)
	{
		if (ft_sp(arg[i]))
			count++;
		i++;
		return (count);
	}
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
				return (free_split(result, i), NULL);
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
	int		j;
	char		**result;

	if (!s)
		return (NULL);
	result = (char **)malloc(sizeof(char *) * (count_world(s, 2) + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s && ft_sp(s[j]))
			s++;
		if (*s)
		{
			result[i] = malloc_word(s, 2);
			if (!result)
				return (free_split(result, i), NULL);
			i++;
			while (*s && !ft_sp(s[j]))
				s++;
		}
	}
	result[i] = NULL;
	return (result);
}
