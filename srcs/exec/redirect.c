/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 11:29:21 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/27 16:19:17 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle_file_error(t_cmd *cmd, t_shell *shell, char *file,
		int exit_error)
{
	ft_putstr_fd("minishell: ", 2);
	if (exit_error == 1)
	{
		if (ft_strchr(file, '/'))
		{
			ft_putstr_fd(file, 2);
			ft_putendl_fd(": Is a directory", 2);
			free_cmd_node(cmd);
			free_shell(shell);
			exit(exit_error);
		}
		ft_putstr_fd("redirect error: ", 2);
	}
	else if (exit_error == 126)
		ft_putstr_fd("Permission denied: ", 2);
	else if (exit_error == 127)
		ft_putstr_fd("No such file or directory: ", 2);
	ft_putendl_fd(file, 2);
	free_cmd_node(cmd);
	free_shell(shell);
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
	if (mode == 0)
	{
		if (access(file, F_OK) != 0)
			handle_file_error(cmd, shell, file, 1);
		if (access(file, R_OK) != 0)
		{
			ft_putstr_fd("minishell: Permission denied: ", 2);
			ft_putendl_fd(file, 2);
			handle_file_error(cmd, shell, file, 126);
		}
	}
	else if (mode == 1)
	{
		if (access(file, F_OK) == 0 && access(file, W_OK) != 0)
		{
			ft_putstr_fd("minishell: Permission denied: ", 2);
			ft_putendl_fd(file, 2);
			handle_file_error(cmd, shell, file, 126);
		}
	}
}

void	redirect_input(t_cmd *cmd, t_shell *shell, int pipe_in)
{
	int	infile;

	if (cmd->is_here_doc)
		handle_here_doc(cmd, shell);
	if (cmd->infile)
	{
		check_file_permission(cmd, shell, cmd->infile, 0);
		infile = open_file(cmd->infile, O_RDONLY);
		if (infile == -1)
			handle_file_error(cmd, shell, cmd->infile, 1);
		if (dup2(infile, STDIN_FILENO) == -1)
			dup2_exit("infile");
		close(infile);
		if (cmd->is_here_doc)
			close(pipe_in);
	}
	if (pipe_in != -1)
	{
		if (dup2(pipe_in, STDIN_FILENO) == -1)
			dup2_exit("dup2 (redirect_input)");
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
		if (outfile == -1)
			handle_file_error(cmd, shell, cmd->outfile, 1);
		if (dup2(outfile, STDOUT_FILENO) == -1)
			dup2_exit("outfile");
		close(outfile);
	}
	if (pipe_out != -1)
	{
		if (dup2(pipe_out, STDOUT_FILENO) == -1)
			dup2_exit("dup2 (redirect_output)");
		if (pipe_out != -1)
			close(pipe_out);
	}
}
