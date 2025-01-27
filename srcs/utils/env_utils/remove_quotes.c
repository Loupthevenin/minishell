/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 15:56:18 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/27 17:55:36 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*remove_s_quotes(char *s)
{
	char	*result;
	int		len_s;

	if (!s)
		return (NULL);
	len_s = ft_strlen(s);
	if (len_s < 2 || (s[0] != '"' && s[0] != '\'') || s[len_s - 1] != s[0])
		return (ft_strdup(s));
	result = (char *)malloc(sizeof(char) * (len_s - 1));
	if (!result)
		return (NULL);
	ft_strlcpy(result, s + 1, len_s - 1);
	result[len_s - 2] = '\0';
	return (result);
}

static int	check_quotes(char *arg, int *in_single_quote, int *in_double_quote,
		int *k)
{
	if (arg[*k] == '\'' && !*in_double_quote)
	{
		*in_single_quote = !*in_single_quote;
		(*k)++;
		return (1);
	}
	else if (arg[*k] == '"' && !*in_single_quote)
	{
		*in_double_quote = !*in_double_quote;
		(*k)++;
		return (1);
	}
	return (0);
}

static void	second_loop(char *arg, char *new_arg, int len)
{
	int	j;
	int	k;
	int	in_single_quote;
	int	in_double_quote;

	j = 0;
	k = 0;
	in_single_quote = 0;
	in_double_quote = 0;
	while (k < len)
	{
		if (check_quotes(arg, &in_single_quote, &in_double_quote, &k))
			continue ;
		new_arg[j++] = arg[k++];
	}
	new_arg[j] = '\0';
}

void	remove_quotes(t_cmd **cmd)
{
	char	**args;
	char	*new_arg;
	int		i;
	int		len;

	args = (*cmd)->args;
	i = 0;
	while (args[i])
	{
		len = ft_strlen(args[i]);
		new_arg = malloc(sizeof(char) * (len + 1));
		if (!new_arg)
			return ;
		second_loop(args[i], new_arg, len);
		free(args[i]);
		args[i] = new_arg;
		i++;
	}
}
