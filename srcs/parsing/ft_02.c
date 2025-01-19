/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_02.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kleung-t <kleung-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 18:24:42 by kleung-t          #+#    #+#             */
/*   Updated: 2025/01/19 17:18:22 by kleung-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//returns 1 if found
int	if_cmd(const char *s)
{
	if (s[0] == 0)
		return (0);
	else if (cmp(s, "ls") || cmp(s, "echo")
		|| cmp(s, "pwd") || cmp(s, "export") || cmp(s, "env"))
		return (1);
	else
		return (0);
}

//returns 1 if found
int	if_sub_cmd(const char *s)
{
	if (s[0] == 0)
		return (0);
	else if (cmp(s, "-n") || cmp(s, "-l"))
		return (1);
	else
		return (0);
}

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

// return 1 if identical
int	ft_sp(char c)
{
	if ((c >= 7 && c <= 13) || c == 32 || c == 0)
		return (1);
	else
		return (0);
}
