/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_id02.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kleung-t <kleung-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 19:31:49 by kleung-t          #+#    #+#             */
/*   Updated: 2025/01/25 19:37:46 by kleung-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

//	err_msg | print_op | op_right | op_left | op_slash

/*

//err msg list
char	*err_msg(int i)
{
	char	*msg;

	if (i == 1)
		msg = ft_strdup("syntax error near unexpected token ");
	else if (i == 2)
		msg = ft_strdup(": Is a directory\n");
	else
		msg = ft_strdup("Unknown error message\n");
	return (msg);
}

// extends op
char	*print_op(char c, int i)
{
	int		j;
	char	*p2;

	j = 0;
	p2 = malloc(sizeof(char) * i + 2);
	while (j <= i)
	{
		if (j == 0)
			p2[j++] = 39;
		p2[j++] = c;
	}
	p2[j++] = 39;
	p2[j++] = '\n';
	p2[j] = 0;
	return (p2);
}

// -> >
char	*op_right_arrow(int i, char c, int index)
{
	char		*p1;
	char		*p2;
	char		*msg;

	p1 = ft_strdup(err_msg(1));
	if (index == 1)
		p2 = ft_strdup("'newline'");
	else
		p2 = ft_strdup(print_op(c, i));
	msg = ft_strjoin(p1, p2);
	return (msg);
}

// -> <
char	*op_left_arrow(int i, char c, int index)
{
	char		*p1;
	char		*p2;
	char		*msg;

	p1 = ft_strdup(err_msg(1));
	if (index == 1)
		p2 = ft_strdup("'newline'");
	else
		p2 = ft_strdup(print_op(c, i));
	msg = ft_strjoin(p1, p2);
	return (msg);
}

// -> /
char	*op_slash(int i, char c)
{
	char		*p1;
	char		*p2;
	char		*msg;
	int			j;

	j = 0;
	if (j <= i)
	{
		p1 = malloc(sizeof(char) * i + 1);
		while (j < i)
			p1[j++] = c;
		p1[j] = 0;
		p2 = ft_strdup(err_msg(2));
		msg = ft_strjoin(p1, p2);
	}
	return (msg);
}
*/