/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_permission.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 12:10:27 by ltheveni          #+#    #+#             */
/*   Updated: 2025/02/03 10:06:42 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_access_in(t_shell *shell, char *file)
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
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file, 2);
		ft_putendl_fd(": Permission denied", 2);
		shell->last_exit = EXIT_FAILURE;
		return (0);
	}
	return (1);
}

static int	check_permission_in(t_shell *shell, char *file)
{
	int	infile;

	if (!check_access_in(shell, file))
		return (0);
	infile = open_file(file, O_RDONLY);
	if (infile == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(file);
		shell->last_exit = 1;
		return (0);
	}
	close(infile);
	return (1);
}

static int	check_permission_out(t_shell *shell, t_redirects *redir)
{
	int	file;

	if (access(redir->outfile, F_OK) == 0 && access(redir->outfile, W_OK) != 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(redir->outfile, 2);
		ft_putendl_fd(": Permission denied", 2);
		shell->last_exit = EXIT_FAILURE;
		return (0);
	}
	if (redir->is_append)
		file = open_file(redir->outfile, O_WRONLY | O_CREAT | O_APPEND);
	else
		file = open_file(redir->outfile, O_WRONLY | O_CREAT | O_TRUNC);
	if (file == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(redir->outfile);
		shell->last_exit = 1;
		return (0);
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
		if (redir->outfile)
			if (!check_permission_out(shell, redir))
				return (0);
		redir = redir->next;
	}
	return (1);
}
