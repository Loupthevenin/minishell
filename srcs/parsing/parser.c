/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kleung-t <kleung-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 14:02:48 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/08 15:01:14 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*parse_input(char *input);

// if space
int	ft_sp(char c)
{
	if ((c >= 7 && c <= 13) || c == 32 || c == 0)
		return (1);
	else
		return (0);
}

// create argument
char	*cr_arg(const char *s, int j)
{
	int		i;
	int		len;
	char	*str;

	i = 0;
	len = 0;
	while (s[j + len] && !ft_sp(s[j + len]))
		len++;
	str = (char *)malloc(sizeof(char) * len + 1);
	while (i <= len && !ft_sp(s[j + i]))
	{
		if (!str)
			free(str);
		str[i] = s[j + i];
		i++;
	}
	str[i] = 0;
	printf("[%s]\n", str);
	return (str);
}

// counts arguments
int	ft_count(const char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (!ft_sp(s[i]) && ft_sp(s[i + 1]))
			count++;
		i++;
	}
	printf("[nb = %d]\n", count);
	return (count);
}

char	*split_arg(char *s)
{
	int		i;
	int		j;
	int		nb;
	char	**substr;
	t_cmd	*cmd;

	i = 0;
	j = 0;
	nb = ft_count(s);
	substr = malloc(sizeof(char *) * nb + 1);
	cmd = malloc(sizeof(t_cmd));
	if (!substr)
		return (NULL);
	while (i < nb && s[j])
	{
		if (!ft_sp(s[j]))
		{
			cmd->args = cr_arg(s, j);
			while (!ft_sp(s[j]))
				j++;
		}
		while (ft_sp(s[j]))
			j++;
		i++;
	}
	return (0);
}
