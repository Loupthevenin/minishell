/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_permission.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 12:10:27 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/29 15:09:55 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_permission_in(t_shell *shell, char *file)
{
	if (access(file, F_OK) != 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file, 2);
		ft_putendl_fd(": No such file or directory", 2);
		shell->last_exit = EXIT_FAILURE;
		return (0);
	}
	if (access(file, R_OK) != 0)
	{
		ft_putstr_fd("minishell: Permission denied: ", 2);
		ft_putendl_fd(file, 2);
		shell->last_exit = 126;
		return (0);
	}
	return (1);
}

static int	check_permission_out(t_shell *shell, char *file)
{
	if (access(file, F_OK) == 0)
	{
		if (access(file, W_OK) != 0)
		{
			ft_putstr_fd("minishell: Permission denied: ", 2);
			ft_putendl_fd(file, 2);
			shell->last_exit = 126;
			return (0);
		}
	}
	return (1);
}

int	check_file_permission(t_cmd *cmd, t_shell *shell)
{
	t_redirects	*redir;

	redir = cmd->redirects;
	while (redir)
	{
		if (redir->infile)
			if (!check_permission_in(shell, redir->infile))
				return (0);
		redir = redir->next;
	}
	redir = cmd->redirects;
	while (redir)
	{
		if (redir->outfile)
			if (!check_permission_out(shell, redir->outfile))
				return (0);
		redir = redir->next;
	}
	return (1);
}
