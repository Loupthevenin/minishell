/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_here_docs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 15:35:36 by ltheveni          #+#    #+#             */
/*   Updated: 2025/02/02 15:50:17 by ltheveni         ###   ########.fr       */
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

int	break_here_doc(t_redirects *current, char *line)
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

int	check_here_docs(t_cmd *cmd, t_shell *shell)
{
	t_cmd		*current;
	t_redirects	*cur_redir;

	current = cmd;
	while (current)
	{
		cur_redir = current->redirects;
		while (cur_redir)
		{
			if (cur_redir->is_here_doc)
			{
				handle_here_doc(current, shell, cur_redir);
				if (g_signal == SIGINT)
				{
					shell->last_exit = 130;
					g_signal = 0;
					return (0);
				}
			}
			cur_redir = cur_redir->next;
		}
		current = current->next;
	}
	return (1);
}
