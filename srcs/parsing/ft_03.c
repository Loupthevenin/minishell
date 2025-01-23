/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_03.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kleung-t <kleung-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:38:26 by kleung-t          #+#    #+#             */
/*   Updated: 2025/01/23 15:38:26 by kleung-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//	len_tab | fill_args | mall_tab

// for tab
int	len_tab(const char *s, int i)
{
	int	count;

	count = 0;
	while (s[i + count])
	{
		while (s[i + count] && cmp_char('|', s[i + count]))
			i++;
		while (s[i + count] && !cmp_char('|', s[i + count]))
			count++;
		printf("len_02 = [%c] OK\n", s[i + count]);
		printf("len_02 = [%d] OK\n", count);
		return (count);
	}
	return (count);
}

// for tab
char	*fill_args(const char *s, int j, char *result)
{
	int		k;

	k = 0;
	while (s[k])
	{
		j = 0;
		while (s[k] && cmp_char('|', s[k]))
			k++;
		while (s[k] && !cmp_char('|', s[k]))
			result[j++] = s[k++];
		result[j] = 0;
	}
	result[j] = 0;
	return (result);
}

// for tab
char	*mall_tab(const char *s, int i, char *result)
{
	int		j;
	int		k;

	j = 0;
	while (s[i])
	{
		k = len_tab(s, i) + 1;
		result = malloc(sizeof(char) * k);
		i += k;
		j++;
	}
	result[j] = 0;
	return (result);
}

// split + fill args on OP
char	**create_tab(const char *s, char **tab)
{
	int	j;
	int	i;

	i = 0;
	j = 0;
	while (s[i])
	{
		tab[j] = mall_tab(s, i, tab[j]);
		tab[j] = fill_args(s, i, tab[j]);
		while (s[i] && if_op_char(s, i))
			i++;
		while (s[i] && !if_op_char(s, i))
			i++;
		if (s[i] && if_op_char(s, i))
			i++;
		j++;
	}
	return (tab);
}
