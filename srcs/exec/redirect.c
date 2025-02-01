/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 11:29:21 by ltheveni          #+#    #+#             */
/*   Updated: 2025/02/01 21:24:01 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	open_file(char *file, int flags)
{
	int	fd;

	fd = open(file, flags, 0644);
	return (fd);
}

static void	handle_redirect_in(t_cmd *cmd, t_shell *shell, t_redirects *current,
		int pipe_in)
{
	int	infile;

	infile = open_file(current->infile, O_RDONLY);
	if (infile == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(current->infile);
		free_cmd_node(cmd);
		free_shell(shell);
		exit(1);
	}
	if (dup2(infile, STDIN_FILENO) == -1)
		dup2_exit("infile");
	close(infile);
	if (pipe_in != -1)
		close(pipe_in);
}

void	redirect_input(t_cmd *cmd, t_shell *shell, int pipe_in)
{
	t_redirects	*current;

	current = cmd->redirects;
	while (current)
	{
		if (current->infile)
			handle_redirect_in(cmd, shell, current, pipe_in);
		current = current->next;
	}
}

static void	handle_redirect_out(t_cmd *cmd, t_shell *shell,
		t_redirects *current)
{
	int	outfile;

	if (current->is_append)
		outfile = open_file(current->outfile,
				O_WRONLY | O_CREAT | O_APPEND);
	else
		outfile = open_file(current->outfile,
				O_WRONLY | O_CREAT | O_TRUNC);
	if (outfile == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(current->outfile);
		free_cmd_node(cmd);
		free_shell(shell);
		exit(1);
	}
	if (current->next)
		close(outfile);
	else
	{
		if (dup2(outfile, STDOUT_FILENO) == -1)
			dup2_exit("outfile");
		close(outfile);
	}
}

void	redirect_output(t_cmd *cmd, t_shell *shell)
{
	t_redirects	*current;

	current = cmd->redirects;
	while (current)
	{
		if (current->outfile)
			handle_redirect_out(cmd, shell, current);
		current = current->next;
	}
}
