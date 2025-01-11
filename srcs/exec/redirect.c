/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 11:29:21 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/11 11:29:55 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	redirect_input(int infile)
{
	if (infile >= 0 && infile != STDIN_FILENO)
	{
		if (dup2(infile, STDIN_FILENO) == -1)
		{
			exit(EXIT_FAILURE);
		}
		close(infile);
	}
}

static void	redirect_output(int outfile)
{
	if (outfile >= 0 && outfile != STDOUT_FILENO)
	{
		if (dup2(outfile, STDOUT_FILENO) == -1)
		{
			exit(EXIT_FAILURE);
		}
		close(outfile);
	}
}

void	redirect(int i, t_cmd *cmd, t_shell *shell)
{
	if (shell->n_pipes == 0)
	{
		redirect_input(cmd->infile);
		redirect_output(cmd->outfile);
	}
	else
	{
		if (i == 0)
		{
			redirect_input(cmd->infile);
			redirect_output(shell->pipefd[i][1]);
		}
		else if (i == shell->n_pipes)
		{
			redirect_input(shell->pipefd[i - 1][0]);
			redirect_output(cmd->outfile);
		}
		else
		{
			redirect_input(shell->pipefd[i - 1][0]);
			redirect_output(shell->pipefd[i][1]);
		}
	}
	close_pipes(shell->pipefd, shell->n_pipes);
}
