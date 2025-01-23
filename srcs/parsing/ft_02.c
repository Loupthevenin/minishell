/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_02.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kleung-t <kleung-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 18:24:42 by kleung-t          #+#    #+#             */
/*   Updated: 2025/01/23 17:15:21 by kleung-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//	if_op_char | if_op | if_cmd | if_sub_cmd | cmp

// returns 1 if identical
int	if_op_char(const char *s, int i)
{
	if (!s)
		return (0);
	if (s[i] == '<' || s[i] == '>')
		return (1);
	return (0);
}

// returns 1 if identical
int	if_op(const char *s)
{
	if (!s || !*s)
		return (0);
	if (!strncmp(s, "<<", 2) || !strncmp(s, ">>", 2))
		return (1);
	if (*s == '<' || *s == '>')
		return (1);
	return (0);
}

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


// return 1 if identical
int	ft_sp(char c)
{
	if ((c >= 7 && c <= 13) || c == 32 || c == 0)
		return (1);
	else
		return (0);
}
