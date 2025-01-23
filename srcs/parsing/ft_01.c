/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_01.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kleung-t <kleung-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 18:24:36 by kleung-t          #+#    #+#             */
/*   Updated: 2025/01/23 16:41:04 by kleung-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// 	cmp | ft_join | ft_dup | set_args

// returns 1 if identical
int	cmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		if (s1[i] == s2[i])
			i++;
		else
			return (0);
	}
	return (1);
}

//adds [s2] after [s1]
char	*ft_join(char *s1, char *s2)
{
	char	*tmp;
	int		i;
	int		j;

	j = (ft_strlen(s1) + ft_strlen(s2));
	i = 0;
	tmp = malloc(sizeof(char) * j + 2);
	while (s1[i])
	{
		tmp[i] = s1[i];
		i++;
	}
	tmp[i++] = ' ';
	while (s2[j])
	{
		tmp[i + j] = s2[j];
		j++;
	}
	tmp[i + j] = 0;
	return (tmp);
}

//s1 in s2
char	*ft_dup(char *s1, char *s2)
{
	int	i;

	i = 0;
	s2 = malloc(sizeof(char) * ft_strlen(s1) + 1);
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = 0;
	return (s2);
}

char	**set_args(char **s, t_cmd *cmd)
{
	int			j;
	int			i;

	j = 0;
	i = 0;
	while (s[i])
		printf("first s%d = [%s]\n", i, s[i]);
	cmd->args = malloc(sizeof(char *) * (i + 1));
	while (s[j])
	{
		if (if_cmd(s[j]))
			split_cmd(s, j, cmd);
	}
	cmd->args[j] = 0;
	return (s);
}
