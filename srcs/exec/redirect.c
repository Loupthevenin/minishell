/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 11:29:21 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/16 17:33:59 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle_file_error(t_cmd *cmd, t_shell *shell, int exit_error)
{
	free_cmd_node(cmd);
	free_shell(shell);
	shell->last_exit = exit_error;
	exit(exit_error);
}

static int	open_file(char *file, int flags)
{
	int	fd;

	fd = open(file, flags, 0644);
	return (fd);
}

static void	check_file_permission(t_cmd *cmd, t_shell *shell, char *file,
		int mode)
{
	if (access(file, F_OK) != 0 && mode == 0)
	{
		ft_putstr_fd("minishell: No such file or directory: ", 2);
		ft_putendl_fd(file, 2);
		handle_file_error(cmd, shell, 127);
	}
	if (mode == 0)
	{
		if (access(file, R_OK) != 0)
		{
			ft_putstr_fd("minishell: Permission denied: ", 2);
			ft_putendl_fd(file, 2);
			handle_file_error(cmd, shell, 126);
		}
	}
	else if (mode == 1)
	{
		if (access(file, W_OK) != 0)
		{
			ft_putstr_fd("minishell: Permission denied: ", 2);
			ft_putendl_fd(file, 2);
			handle_file_error(cmd, shell, 126);
		}
	}
}

void	redirect_input(t_cmd *cmd, t_shell *shell, int pipe_in)
{
	int	infile;

	if (cmd->infile)
	{
		check_file_permission(cmd, shell, cmd->infile, 0);
		infile = open_file(cmd->infile, O_RDONLY);
		if (dup2(infile, STDIN_FILENO) == -1)
		{
			perror("infile");
			exit(EXIT_FAILURE);
		}
		close(infile);
	}
	if (pipe_in != -1)
	{
		if (dup2(pipe_in, STDIN_FILENO) == -1)
		{
			perror("dup2 (redirect_input)");
			exit(EXIT_FAILURE);
		}
		close(pipe_in);
	}
}

void	redirect_output(t_cmd *cmd, t_shell *shell, int pipe_out)
{
	int	outfile;

	if (cmd->outfile)
	{
		check_file_permission(cmd, shell, cmd->outfile, 1);
		if (cmd->is_append)
			outfile = open_file(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND);
		else
			outfile = open_file(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC);
		if (dup2(outfile, STDOUT_FILENO) == -1)
		{
			perror("outfile");
			exit(EXIT_FAILURE);
		}
		close(outfile);
	}
	if (pipe_out != -1)
	{
		if (dup2(pipe_out, STDOUT_FILENO) == -1)
		{
			perror("dup2 (redirect_output)");
			exit(EXIT_FAILURE);
		}
		close(pipe_out);
	}
}
