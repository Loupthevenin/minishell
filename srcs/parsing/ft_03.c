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

//	len_tab | fill_args | mall_tab

// for tab
int	len_tab(const char *s, int i)
{
	int	count;

	count = 0;
	while (s[i + count])
	{
		while (s[i + count] && cmp('|', s[i + count]))
			i++;
		while (s[i + count] && !cmp('|', s[i + count]))
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
		while (s[k] && cmp('|', s[k]))
			k++;
		while (s[k] && !cmp('|', s[k]))
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
	while (s[i])
	{
		temp[j] = mall_tab(s, i, temp[j]);
		temp[j] = fill_args(s, i, temp[j]);
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
