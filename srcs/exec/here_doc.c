/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 08:33:36 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/17 10:45:09 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	break_here_doc(t_cmd *cmd, char *line)
{
	char	*delimiter;
	size_t	len_delimiter;
	size_t	len_line;

	delimiter = cmd->delimiter_here_doc;
	len_delimiter = ft_strlen(delimiter);
	len_line = ft_strlen(line);
	if (!line)
		return (1);
	if ((len_delimiter == 0 && len_line == 1 && line[0] == '\n'))
	{
		free(line);
		return (1);
	}
	if (len_delimiter > 0 && !ft_strncmp(line, delimiter, len_delimiter)
		&& line[len_delimiter] == '\n')
	{
		free(line);
		return (1);
	}
	return (0);
}

void	handle_here_doc(t_cmd *cmd, t_shell *shell)
{
	char	*line;
	char	*tmp_file;
	int		fd;

	tmp_file = "/tmp/.here_doc_tmp";
	fd = open(tmp_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("Error creating here_doc");
		free_cmd_node(cmd);
		free_shell(shell);
		shell->last_exit = EXIT_FAILURE;
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		line = readline("here_doc> ");
		if (break_here_doc(cmd, line))
			break ;
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);
	cmd->infile = ft_strdup(tmp_file);
}
