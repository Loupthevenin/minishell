/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_id01.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kleung-t <kleung-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 19:31:06 by kleung-t          #+#    #+#             */
/*   Updated: 2025/01/25 19:37:31 by kleung-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

//	nb_op2 | nb_op | ft_op_limit | treat_checked | check_input

/*

// follow nb_op
char	*nb_op2(char c, int i, int limit)
{
	int		j;
	char	*msg;

	j = i % limit;
	if (j == 1)
	{
		if (c == '<')
			msg = ft_strdup(op_left_arrow(j, c, 2));
		if (c == '>')
			msg = ft_strdup(op_right_arrow(j, c, 2));
	}
	else if (j == 2)
	{
		if (c == '<')
			msg = ft_strdup(op_left_arrow(j, c, 2));
	}
	else if (j == 0)
	{
		if (c == '<')
			msg = ft_strdup(op_left_arrow(j, c, 2));
		if (c == '>')
			msg = ft_strdup(op_right_arrow(j, c, 2));
	}
	return (msg);
}

// print of the op needed
char	*nb_op(char c, int i, int limit)
{
	int		j;
	char	*msg;

	if (c == '/')
		msg = ft_strdup(op_slash(i, c));
	if (i <= limit)
	{
		j = i % limit;
		if (c == '<')
			msg = ft_strdup(op_left_arrow(j, c, 1));
		if (c == '>')
			msg = ft_strdup(op_right_arrow(j, c, 1));
	}
	else if (i > limit && i < (limit * 2))
		msg = ft_strdup(nb_op2(c, i, limit));
	else
	{
		if (c == '<')
			msg = ft_strdup(op_left_arrow(3, c, 2));
		else if (c == '>')
			msg = ft_strdup(op_right_arrow(2, c, 2));
	}
	return (msg);
}

// defines limit of print op
int	ft_op_limit(char c)
{
	int	limit;

	if (c == '/')
		limit = 1;
	if (c == '>')
		limit = 2;
	if (c == '<')
		limit = 3;
	return (limit);
}

// nb of op found
int	treat_checked(char *s, int i)
{
	int		j;
	char	c;

	c = s[i];
	j = 0;
	while (s[i + j])
	{
		while (s[i + j] == c)
			j++;
	}
	return (j);
}

char	*check_input(char *input)
{
	int		i;
	int		j;
	int		limit;
	char	*s;

	i = 0;
	while (input[i])
	{
		if (input[i] == '/' || input[i] == '<' || input[i] == '>')
		{
			limit = ft_op_limit(input[i]);
			printf("Limit = %d \n", limit);
			j = treat_checked(input, i);
			printf("Treat checked = %d \n", j);
			s = ft_strdup(nb_op(input[i], j, limit));
			printf("nb op = %s\n", s);
			i += j;
			j = 0;
		}
		i++;
	}
	return (s);
}
*/