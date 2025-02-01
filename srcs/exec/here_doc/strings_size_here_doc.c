/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings_size_here_doc.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 20:57:57 by ltheveni          #+#    #+#             */
/*   Updated: 2025/02/01 20:59:28 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char	*set_value(const char *input)
{
	char	*result;
	int		i;

	i = 0;
	while (ft_isalnum(input[i]) || input[i] == '_')
		i++;
	result = malloc(sizeof(char) * (i + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (ft_isalnum(*input) || *input == '_')
		result[i++] = *input++;
	result[i] = '\0';
	return (result);
}

static int	set_count_env_var(t_shell *shell, const char **input)
{
	char	*key;
	char	*value;
	int		count;

	(*input)++;
	count = 0;
	key = set_value(*input);
	if (key)
	{
		value = get_value_env(shell->env_list, key);
		if (value)
			count += ft_strlen(value);
		free(key);
	}
	while (ft_isalnum(**input) || **input == '_')
		(*input)++;
	return (count);
}

static int	handle_dollar(const char **input, t_shell *shell)
{
	int	count;

	count = 0;
	if (*(*input + 1) == '?' || ft_isalnum(*(*input + 1)) || *(*input
			+ 1) == '_')
	{
		if (*(*input + 1) == '?')
		{
			count += ft_nbrlen(shell->last_exit);
			(*input) += 2;
			return (count);
		}
		else if (ft_isalnum(*(*input + 1)) || *(*input + 1) == '_')
			return (set_count_env_var(shell, input));
	}
	else
	{
		count++;
		(*input)++;
	}
	return (count);
}

int	strings_size_here_doc(const char *input, t_shell *shell)
{
	int	count;

	count = 0;
	while (*input)
	{
		if (*input == '$')
		{
			count += handle_dollar(&input, shell);
			continue ;
		}
		count++;
		input++;
	}
	return (count);
}
