/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splits.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kleung-t <kleung-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 09:52:09 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/19 21:19:49 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// 1 = OP, 2 = TOKEN
char	*malloc_word_arg(const char *s, int delimiter_type)
{
	int		i;
	char	*word;

	i = 0;
	while (s[i] && ((delimiter_type == 1 && !if_op(s)) || (delimiter_type == 2
				&& !ft_sp(s[i]))))
		i++;
	word = (char *)malloc(sizeof(char) * (i + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (s[i] && ((delimiter_type == 1 && !if_op(s)) || (delimiter_type == 2
				&& !ft_sp(s[i]))))
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

// 1 = OP, 2 = TOKEN
int	count_word(const char *arg, int code)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	while (arg[i])
	{
		if ((code == 1 && if_op_char(arg, i)) || (code == 2 && !ft_sp(arg[i])))
		{
			count++;
			while (arg[i] && ((code == 1 && if_op_char(arg, i)) || (code == 2
						&& !ft_sp(arg[i]))))
				i++;
		}
		i++;
	}
	return (count);
}

char	**split_cmd(char **s, int j, t_cmd *cmd)
{
	cmd->args[j] = ft_dup(s[j], cmd->args[j]);
	printf("0 = [%s]\n", cmd->args[j]);
	j++;
	while (s[j])
	{
		if (s[j][0] == '-' && if_sub_cmd(s[j]))
		{
			cmd->args[j] = ft_dup(s[j], cmd->args[j]);
			printf("%s is sub_cmd\n", cmd->args[j]);
		}
		else if (if_op(s[j]))
		{
			printf("Create a new node with %s\n", cmd->args[j]);
			return (0);
		}
		else
		{
			cmd->args[j] = ft_dup(s[j], cmd->args[j]);
			printf("%s is other\n", cmd->args[j]);
		}
		j++;
	}
	return (NULL);
}

// split on operators
char	**split_input(const char *s)
{
	int		i;
	char	**result;

	if (!s)
		return (NULL);
	result = (char **)malloc(sizeof(char *) * (count_word(s, 1) + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s && if_op_char(s, i))
			s++;
		if (*s)
		{
			result[i] = malloc_word_arg(s, 1);
			if (!result)
				return (free_tab((void **)result, i, 0), NULL);
			i++;
			while (*s && !if_op_char(s, i))
				s++;
		}
	}
	result[i] = NULL;
	return (result);
}

// split on spaces
char	**split_arg(const char *s)
{
	int		i;
	char	**result;

	if (!s)
		return (NULL);
	result = (char **)malloc(sizeof(char *) * (count_word(s, 2) + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s && ft_sp(*s))
			s++;
		if (*s)
		{
			result[i] = malloc_word_arg(s, 2);
			if (!result)
				return (free_tab((void **)result, 0, 1), NULL);
			i++;
			while (*s && !ft_sp(*s))
				s++;
		}
	}
	result[i] = NULL;
	return (result);
}
