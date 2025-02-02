/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 08:33:36 by ltheveni          #+#    #+#             */
/*   Updated: 2025/02/02 15:52:08 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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

	signal(SIGINT, handle_signal_here_doc);
	while (1)
	{
		line = readline("> ");
		if (break_here_doc(current, line))
			break ;
		if (g_signal == SIGINT)
		{
			free(line);
			break ;
		}
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

static int	open_here_doc(char *tmp_file, t_cmd *cmd, t_shell *shell)
{
	int	fd;

	fd = open(tmp_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("Error creating here_doc");
		free_cmd_node(cmd);
		free_shell(shell);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

void	handle_here_doc(t_cmd *cmd, t_shell *shell, t_redirects *current)
{
	char	*tmp_file;
	int		fd;
	int		expand;
	char	*clean_delimiter;

	tmp_file = "/tmp/.here_doc_tmp";
	fd = open_here_doc(tmp_file, cmd, shell);
	expand = !is_quoted_delimiter(current->delimiter_here_doc);
	clean_delimiter = rm_quotes(current->delimiter_here_doc);
	if (clean_delimiter && clean_delimiter != current->delimiter_here_doc)
	{
		free(current->delimiter_here_doc);
		current->delimiter_here_doc = clean_delimiter;
	}
	handle_loop_here_doc(shell, fd, expand, current);
	close(fd);
	if (g_signal == SIGINT)
	{
		unlink(tmp_file);
		setup_signals(1);
		return ;
	}
	current->infile = ft_strdup(tmp_file);
}
