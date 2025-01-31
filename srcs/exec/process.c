/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 11:39:41 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/31 17:17:59 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	close_pipes_error(int pipe_in, int *fd)
{
	if (pipe_in != -1)
		close(pipe_in);
	if (fd[0] != -1)
		close(fd[0]);
	if (fd[1] != -1)
		close(fd[1]);
}

static char	**get_envp(t_shell *shell, t_cmd *cmd)
{
	char	**envp;

	envp = list_to_double_array(shell->env_list);
	if (!envp)
	{
		perror("minishell: failed alloc memory environment");
		handle_error_process(cmd, shell, envp, EXIT_FAILURE);
	}
	return (envp);
}

static char	*handle_get_cmd(t_cmd *cmd, char **envp, int pipe_in, int *fd)
{
	char	*cmd_path;

	cmd_path = get_cmd_path(cmd->args[0], envp);
	if (!cmd_path)
	{
		close_pipes_error(pipe_in, fd);
	}
	return (cmd_path);
}

static int	check_permission_cmd(char *cmd_path, int pipe_in, int *fd)
{
	if (access(cmd_path, F_OK) != 0)
	{
		close_pipes_error(pipe_in, fd);
		return (127);
	}
	if (access(cmd_path, X_OK) != 0)
	{
		close_pipes_error(pipe_in, fd);
		return (126);
	}
	return (0);
}

void	process(t_cmd *cmd, t_shell *shell, int pipe_in, int *fd)
{
	char	*cmd_path;
	char	**envp;
	int		exit_error;

	envp = get_envp(shell, cmd);
	cmd_path = handle_get_cmd(cmd, envp, pipe_in, fd);
	if (!cmd_path)
		handle_error_file(cmd, shell, envp);
	exit_error = check_permission_cmd(cmd_path, pipe_in, fd);
	if (exit_error == 126)
		handle_error_execve(cmd, shell, envp, 126);
	else if (exit_error == 127)
		handle_error_execve(cmd, shell, envp, 127);
	execve(cmd_path, cmd->args, envp);
	free(cmd_path);
	if (errno == EACCES || errno == ENOENT)
	{
		close_pipes_error(pipe_in, fd);
		if (errno == EACCES)
			handle_error_execve(cmd, shell, envp, 126);
		else
			handle_error_execve(cmd, shell, envp, 127);
	}
	perror("minishell");
	handle_error_process(cmd, shell, envp, EXIT_FAILURE);
}
