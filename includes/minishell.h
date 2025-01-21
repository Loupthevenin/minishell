/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 00:10:54 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/21 19:28:34 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "ft_printf.h"
# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdlib.h>
# include <sys/wait.h>

typedef struct s_cmd
{
	char			**args;
	char			*op;
	char			*infile;
	char			*outfile;
	int				is_append;
	int				is_here_doc;
	char			*delimiter_here_doc;
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
char				*get_value_env(t_env *env, const char *key);
long long			ft_atoi_exit(const char *str, int *overflow);

// utils cmd
t_cmd				*create_node(char **args);
void				append_node(t_cmd **head, t_cmd *new_node);
int					get_command_count(t_cmd *head);
void				free_cmd_node(t_cmd *head);
void				free_env_node(t_env *head);

// utils env
t_env				*double_array_to_list(char **envp);
char				**list_to_double_array(t_env *env);
void				selection_sort_env(char **array, int size);
int					check_identifier_unset(char *s);
int					check_identifier_export(char *s);
int					get_size_env(t_env *env);

// parsing
int					cmp(const char *s1, const char *s2);
char				*ft_join(char *s1, char *s2);
char				*ft_dup(char *s1, char *s2);
char				**split_cmd(char **s, int j, t_cmd *cmd);
char				**set_args(char **s, t_cmd *cmd);
int					if_op(const char *s);
int					if_op_char(const char *s, int i);
int					if_cmd(const char *s);
int					if_sub_cmd(const char *s);
int					ft_sp(char c);
char				*malloc_word_arg(const char *s, int delimiter_type);
int					count_word(const char *arg, int code);
char				**split_input(const char *s);
char				**split_arg(const char *s);

// exec
void				fork_processes(t_cmd *cmd, t_shell *shell, int *fd,
						int pipe_in);
void				handle_here_doc(t_cmd *cmd, t_shell *shell);
void				redirect_input(t_cmd *cmd, t_shell *shell, int pipe_in);
void				redirect_output(t_cmd *cmd, t_shell *shell, int pipe_out);
void				process(t_cmd *cmd, t_shell *shell);
char				*get_cmd_path(const char *cmd, char **envp);
void				exec_builtins(t_shell *shell, t_cmd *cmd);

// builtins
int					is_builtins(t_cmd *cmd);
void				builtin_echo(t_shell *shell, t_cmd *cmd);
void				builtin_cd(t_shell *shell, t_cmd *cmd);
void				builtin_pwd(t_shell *shell, t_cmd *cmd);
void				builtin_export(t_shell *shell, t_cmd *cmd);
void				builtin_unset(t_shell *shell, t_cmd *cmd);
void				builtin_env(t_shell *shell, t_cmd *cmd);
void				builtin_exit(t_shell *shell, t_cmd *cmd);

// main
void				setup_signals(int is_parent);
t_cmd				*parse_input(const char *input);
void				exec_cmd(t_cmd *cmd, t_shell *shell);
#endif
