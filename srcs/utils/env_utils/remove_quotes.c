/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 15:56:18 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/26 16:25:03 by ltheveni         ###   ########.fr       */
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
	if (len_s < 2 || s[0] != '"' || s[len_s - 1] != '"')
		return (ft_strdup(s));
	result = (char *)malloc(sizeof(char) * (len_s - 1));
	if (!result)
		return (NULL);
	ft_strlcpy(result, s + 1, len_s - 1);
	result[len_s - 2] = '\0';
	return (result);
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
		if (args[i][0] == '"' && args[i][ft_strlen(args[i]) - 1] == '"')
		{
			len = ft_strlen(args[i]);
			new_arg = ft_substr(args[i], 1, len - 2);
			if (new_arg)
			{
				free(args[i]);
				args[i] = new_arg;
			}
		}
		i++;
	}
}
