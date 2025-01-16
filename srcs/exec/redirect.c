/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 11:29:21 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/16 12:40:48 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// open infile here + permission;
void	redirect_input(t_cmd *cmd, int pipe_in)
{
	if (cmd->infile)
	{
		/* if (dup2(cmd->infile, STDIN_FILENO) == -1) */
		/* { */
		/* 	perror("infile"); */
		/* 	exit(EXIT_FAILURE); */
		/* } */
		/* close(cmd->infile); */
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

// open outfile here + permission;
void	redirect_output(t_cmd *cmd, int pipe_out)
{
	if (cmd->outfile)
	{
		/* if (dup2(cmd->outfile, STDOUT_FILENO) == -1) */
		/* { */
		/* 	perror("outfile"); */
		/* 	exit(EXIT_FAILURE); */
		/* } */
		/* close(cmd->outfile); */
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
