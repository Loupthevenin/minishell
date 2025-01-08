/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 11:43:33 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/08 11:44:00 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**get_path_dir(char **envp)
{
	int		i;
	char	*path_value;

	i = 0;
	path_value = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path_value = envp[i] + 5;
			break ;
		}
		i++;
	}
	if (!path_value)
		return (NULL);
	return (ft_split(path_value, ':'));
}

static char	*join_path(const char *dir, const char *cmd)
{
	char	*full_path;
	size_t	len;

	len = ft_strlen(dir) + ft_strlen(cmd) + 2;
	full_path = (char *)malloc(sizeof(char) * (len + 1));
	if (!full_path)
		return (NULL);
	ft_strlcpy(full_path, dir, len);
	ft_strlcat(full_path, "/", len);
	ft_strlcat(full_path, cmd, len);
	return (full_path);
}

static char	*loop_dirs(char **dirs, const char *cmd)
{
	int		i;
	char	*full_path;

	i = 0;
	while (dirs[i])
	{
		full_path = join_path(dirs[i], cmd);
		if (!full_path)
		{
			break ;
		}
		if (access(full_path, X_OK) == 0)
		{
			free_tab(dirs);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_tab(dirs);
	return (NULL);
}

char	*get_cmd_path(const char *cmd, char **envp)
{
	char	**dirs;
	char	*result;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		else
			return (NULL);
	}
	dirs = get_path_dir(envp);
	if (!dirs)
		return (NULL);
	result = loop_dirs(dirs, cmd);
	if (!result)
		return (NULL);
	return (result);
}
