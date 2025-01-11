/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:02:01 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/11 11:30:25 by ltheveni         ###   ########.fr       */
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
	int				infile;
	int				outfile;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_shell
{
	char			**env;
	int				**pipefd;
	pid_t			pid;
	int				n_pipes;
}					t_shell;

// utils
t_cmd				*create_node(char **args);
void				append_node(t_cmd **head, t_cmd *new_node);
int					get_command_count(t_cmd *head);
void				free_tab(void **tabs, int size, int is_null);
void				free_cmd_node(t_cmd *head);
void				close_pipes(int **pipes, int n);

// parsing

// exec
void				fork_processes(t_cmd *cmd, t_shell *shell);
void				redirect(int i, t_cmd *cmd, t_shell *shell);
void				process(t_cmd *cmd, t_shell *shell);
char				*get_cmd_path(const char *cmd, char **envp);
void				exec_builtins(t_cmd *cmd);

// builtins
void				builtin_echo(char **args);
void				builtin_cd(char **args);
void				builtin_pwd(char **args);
void				builtin_export(char **args);
void				builtin_unset(char **args);
void				builtin_env(char **args);
void				builtin_exit(char **args);

// main
t_cmd				*parse_input(char *input);
void				exec_cmd(t_cmd *cmd, t_shell *shell);
#endif
