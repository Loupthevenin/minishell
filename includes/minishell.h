/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:02:01 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/09 09:21:42 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "ft_printf.h"
# include "libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/wait.h>

typedef struct s_cmd
{
	char			**args;
	char			*infile;
	char			*outfile;
	char			*append;
	struct s_cmd	*next;
}					t_cmd;

// utils
t_cmd				*create_node(char **args);
void				append_node(t_cmd **head, t_cmd *new_node);
void				free_tab(char **tabs);
void				free_cmd_node(t_cmd *head);

// Parsing

// exec
char				*get_cmd_path(const char *cmd, char **envp);
void				process(t_cmd *cmd, char **envp);
void				fork_processes(t_cmd *cmd, char **envp);

// main
t_cmd				*parse_input(char *input);
void				exec_cmd(t_cmd *cmd, char **envp);
#endif
