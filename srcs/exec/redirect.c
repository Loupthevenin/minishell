/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 11:29:21 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/12 10:01:26 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	redirect_input(int infile)
{
	if (infile >= 0 && infile != STDIN_FILENO)
	{
		if (dup2(infile, STDIN_FILENO) == -1)
		{
			perror("dup2 (redirect_input)");
			exit(EXIT_FAILURE);
		}
		if (close(infile) == -1)
		{
			perror("close (redirect_input)");
			exit(EXIT_FAILURE);
		}
	}
}

static void	redirect_output(int outfile)
{
	if (outfile >= 0 && outfile != STDOUT_FILENO)
	{
		if (dup2(outfile, STDOUT_FILENO) == -1)
		{
			perror("dup2 (redirect_output");
			exit(EXIT_FAILURE);
		}
		if (close(outfile) == -1)
		{
			perror("close (redirect_output)");
			exit(EXIT_FAILURE);
		}
	}
}

static void	zero_pipe(t_cmd *cmd, t_shell *shell)
{
	(void)shell;
	redirect_input(cmd->infile);
	if (cmd->outfile == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->path_outfile, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		free_cmd_node(cmd);
		exit(126);
	}
	redirect_output(cmd->outfile);
}

static void	n_pipes(t_cmd *cmd, t_shell *shell, int i)
{
	if (i == 0)
	{
		redirect_input(cmd->infile);
		redirect_output(shell->pipefd[i][1]);
	}
	else if (i == shell->n_pipes)
	{
		redirect_input(shell->pipefd[i - 1][0]);
		if (cmd->outfile == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd->path_outfile, 2);
			ft_putstr_fd(": Permission denied\n", 2);
			free_cmd_node(cmd);
			free_tab((void **)shell->pipefd, i + 1, 0);
			exit(126);
		}
		redirect_output(cmd->outfile);
	}
	else
	{
		redirect_input(shell->pipefd[i - 1][0]);
		redirect_output(shell->pipefd[i][1]);
	}
}

void	redirect(int i, t_cmd *cmd, t_shell *shell)
{
	if (shell->n_pipes == 0)
		zero_pipe(cmd, shell);
	else
		n_pipes(cmd, shell, i);
	close_pipes(shell->pipefd, shell->n_pipes);
}
