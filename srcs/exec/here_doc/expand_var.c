/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 20:44:33 by ltheveni          #+#    #+#             */
/*   Updated: 2025/02/01 21:02:44 by ltheveni         ###   ########.fr       */
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

static void	set_env_var(t_shell *shell, int *i, const char **input,
		char *result)
{
	char	*key;
	char	*value;

	(*input)++;
	key = set_value(*input);
	if (key)
	{
		value = get_value_env(shell->env_list, key);
		if (value)
		{
			ft_strlcpy(result + *i, value, ft_strlen(value) + 1);
			*i += ft_strlen(value);
		}
		free(key);
	}
	while (ft_isalnum(**input) || **input == '_')
		(*input)++;
}

static void	handle_dollar(const char **input, char *result, int *i,
		t_shell *shell)
{
	char	*key;

	if (*(*input + 1) == '?' || ft_isalnum(*(*input + 1)) || *(*input
			+ 1) == '_')
	{
		if (*(*input + 1) == '?')
		{
			key = ft_itoa(shell->last_exit);
			if (key)
			{
				ft_strlcpy(result + *i, key, ft_strlen(key) + 1);
				*i += ft_strlen(key);
				free(key);
			}
			(*input) += 2;
		}
		else if (ft_isalnum(*(*input + 1)) || *(*input + 1) == '_')
			set_env_var(shell, i, input, result);
	}
	else
	{
		result[(*i)++] = '$';
		(*input)++;
	}
}

char	*expand_var(const char *line, t_shell *shell)
{
	char	*result;
	int		i;
	int		size;

	i = 0;
	size = strings_size_here_doc(line, shell);
	if (size == -1)
		return (NULL);
	result = malloc(sizeof(char) * (size + 1));
	if (!result)
		return (NULL);
	while (*line)
	{
		if (*line == '$')
		{
			handle_dollar(&line, result, &i, shell);
			continue ;
		}
		result[i++] = *line;
		line++;
	}
	result[i] = '\0';
	return (result);
}
