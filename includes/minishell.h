/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:02:01 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/16 15:02:43 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "ft_printf.h"
# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <sys/wait.h>

typedef struct s_cmd
{
	char			**args;
	char			*infile;
	char			*outfile;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_shell
{
	t_env			*env_list;
	pid_t			pid;
	int				n_pipes;
	int				last_exit;
}					t_shell;

// utils
void				free_tab(void **tabs, int size, int is_null);
void				free_shell(t_shell *shell);

// utils cmd
t_cmd				*create_node(char **args);
void				append_node(t_cmd **head, t_cmd *new_node);
int					get_command_count(t_cmd *head);
void				free_cmd_node(t_cmd *head);

// utils env
t_env				*double_array_to_list(char **envp);
char				**list_to_double_array(t_env *env);

// parsing
int					ft_op(const char *s);

// exec
void				fork_processes(t_cmd *cmd, t_shell *shell, int *fd,
						int pipe_in);
void				redirect_input(t_cmd *cmd, int pipe_in);
void				redirect_output(t_cmd *cmd, int pipe_out);
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
void				setup_signals(int is_parent);
t_cmd				*parse_input(char *input);
void				exec_cmd(t_cmd *cmd, t_shell *shell);
#endif
