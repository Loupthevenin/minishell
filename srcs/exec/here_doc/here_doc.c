/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 08:33:36 by ltheveni          #+#    #+#             */
/*   Updated: 2025/02/01 23:31:37 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	handle_break(size_t len_delimiter, size_t len_line, char *line,
		char *delimiter)
{
	if (len_delimiter == 0)
	{
		if (len_line == 0)
		{
			free(line);
			return (0);
		}
	}
	else
	{
		if (len_line == len_delimiter && !ft_strcmp(line, delimiter))
		{
			free(line);
			return (0);
		}
	}
	return (1);
}

static int	break_here_doc(t_redirects *current, char *line)
{
	char	*delimiter;
	size_t	len_delimiter;
	size_t	len_line;

	if (!line)
		return (1);
	delimiter = current->delimiter_here_doc;
	len_delimiter = ft_strlen(delimiter);
	len_line = ft_strlen(line);
	if (!handle_break(len_delimiter, len_line, line, delimiter))
		return (1);
	return (0);
}

static int	is_quoted_delimiter(char *delimiter)
{
	if (!delimiter)
		return (0);
	if (delimiter[0] == '\'' && delimiter[ft_strlen(delimiter) - 1] == '\'')
		return (1);
	if (delimiter[0] == '"' && delimiter[ft_strlen(delimiter) - 1] == '"')
		return (1);
	return (0);
}

static void	handle_loop_here_doc(t_shell *shell, int fd, int expand,
		t_redirects *current)
{
	char	*expand_line;
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (break_here_doc(current, line))
			break ;
		if (expand)
		{
			expand_line = expand_var(line, shell);
			ft_putendl_fd(expand_line, fd);
			free(expand_line);
		}
		else
			ft_putendl_fd(line, fd);
		free(line);
	}
}

void	handle_here_doc(t_cmd *cmd, t_shell *shell, t_redirects *current)
{
	char	*tmp_file;
	int		fd;
	int		expand;
	char	*clean_delimiter;

	tmp_file = "/tmp/.here_doc_tmp";
	fd = open(tmp_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("Error creating here_doc");
		free_cmd_node(cmd);
		free_shell(shell);
		exit(EXIT_FAILURE);
	}
	expand = !is_quoted_delimiter(current->delimiter_here_doc);
	clean_delimiter = rm_quotes(current->delimiter_here_doc);
	if (clean_delimiter && clean_delimiter != current->delimiter_here_doc)
	{
		free(current->delimiter_here_doc);
		current->delimiter_here_doc = clean_delimiter;
	}
	handle_loop_here_doc(shell, fd, expand, current);
	close(fd);
	current->infile = ft_strdup(tmp_file);
}
