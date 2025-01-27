/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 11:02:13 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/27 12:19:34 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_strlen_double_array(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

static int	check_str(const char *s)
{
	int	i;

	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	error_num_argument(char **args, int mode)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(args[1], 2);
	ft_putendl_fd(": numeric argument required", 2);
	if (mode)
		return (2);
	else
		return (255);
}

static int	exit_status(char **args)
{
	long long	exit_code;
	int			overflow;

	exit_code = 0;
	if (args[1])
	{
		if (!check_str(args[1]))
			return (error_num_argument(args, 1));
		exit_code = ft_atoi_exit(args[1], &overflow);
		if (overflow)
			return (error_num_argument(args, 0));
		if (exit_code > 255 || exit_code < 0)
		{
			exit_code %= 256;
			if (exit_code < 0)
				exit_code += 256;
		}
	}
	return ((int)exit_code);
}

void	builtin_exit(t_shell *shell, t_cmd *cmd)
{
	char	**args;
	int		size_array;
	int		exit_code;

	args = cmd->args;
	size_array = ft_strlen_double_array(args);
	ft_putendl_fd("exit", 1);
	if (size_array > 2)
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		exit_code = EXIT_FAILURE;
		shell->last_exit = exit_code;
		return ;
	}
	else
		exit_code = exit_status(args);
	free_shell(shell);
	free_cmd_node(cmd);
	shell->last_exit = exit_code;
	exit(exit_code);
}
