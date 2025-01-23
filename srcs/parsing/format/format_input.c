/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 08:43:01 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/23 11:38:27 by ltheveni         ###   ########.fr       */
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
	(*input)--;
}

static void	handle_dollar(const char **input, char *result, int *i,
		t_shell *shell)
{
	char	*key;

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

static char	*format_loop(t_shell *shell, const char *input, char *result)
{
	int	in_single_quote;
	int	in_double_quote;
	int	i;

	i = 0;
	in_single_quote = 0;
	in_double_quote = 0;
	while (*input)
	{
		if (*input == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (*input == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		else if (*input == '$' && !in_single_quote)
			handle_dollar(&input, result, &i, shell);
		else
			result[i++] = *input;
		input++;
	}
	result[i] = '\0';
	return (result);
}

char	*format_input(const char *input, t_shell *shell)
{
	char	*result;
	int		size;

	size = strings_size(input, shell);
	if (size == -1)
		return (NULL);
	result = (char *)malloc(sizeof(char) * (size + 1));
	if (!result)
		return (NULL);
	return (format_loop(shell, input, result));
}
