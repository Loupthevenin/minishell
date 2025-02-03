/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kleung-t <kleung-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 00:10:54 by ltheveni          #+#    #+#             */
/*   Updated: 2025/02/03 11:12:42 by ltheveni         ###   ########.fr       */
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
# include <sys/ioctl.h>
# include <sys/wait.h>

typedef struct s_redirects
{
	char				*infile;
	char				*outfile;
	int					is_append;
	int					is_here_doc;
	char				*delimiter_here_doc;
	struct s_redirects	*next;
}						t_redirects;

typedef struct s_cmd
{
	char				**args;
	t_redirects			*redirects;
	struct s_cmd		*next;
}						t_cmd;

typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef struct s_shell
{
	t_env				*env_list;
	pid_t				pid;
	int					n_pipes;
	int					last_exit;
}						t_shell;

typedef struct s_split
{
	int					in_single_quote;
	int					in_double_quote;
	int					start;
	int					index;
}						t_split;

// utils
void					free_tab(void **tabs, int size, int is_null);
void					free_shell(t_shell *shell);
char					*get_value_env(t_env *env, const char *key);
long long				ft_atoi_exit(const char *str, int *overflow);
void					dup2_exit(char *s);

// utils cmd
t_cmd					*create_node(char **args);
void					append_node(t_cmd **head, t_cmd *new_node);
int						get_command_count(t_cmd *head);
void					free_cmd_node(t_cmd *head);
void					free_env_node(t_env *head);

// utils env
t_env					*double_array_to_list(char **envp);
char					**list_to_double_array(t_env *env);
void					selection_sort_env(char **array, int size);
int						check_identifier_unset(char *s);
int						check_identifier_export(char *s);
int						get_size_env(t_env *env);
void					update_env_var(t_env *env, char *key, char *new_value);
void					update_shlvl(t_shell *shell);
t_env					*add_default_env_vars(void);
void					remove_quotes(t_cmd **cmd);
char					*rm_quotes(char *s);

// utils parsing
int						ft_nbrlen(int n);
int						is_quote(char c, t_split *state);
void					rm_element_tab(char **tab, int index_remove);
char					**ft_dup_array(char **args);

// parsing
int						strings_size(const char *input, t_shell *shell);
char					*format_input(const char *input, t_shell *shell);
char					*add_spaces_on_operator(const char *input);
int						if_op(const char *s);
int						ft_sp(char c);
char					**split_input(const char *s);
int						count_word_arg(const char *arg);
char					**split_arg(const char *s);
void					set_operator(t_cmd **new_node);
char					*op_slash(int i, char c);
char					*op_left_arrow(int i, char c, int index);
char					*op_right_arrow(int i, char c, int index);

// exec
int						open_file(char *file, int flags);
int						check_file_permission(t_cmd *cmd, t_shell *shell);
void					fork_processes(t_cmd *cmd, t_shell *shell, int *fd,
							int pipe_in);
int						strings_size_here_doc(const char *input,
							t_shell *shell);
char					*expand_var(const char *line, t_shell *shell);
void					handle_here_doc(t_cmd *cmd, t_shell *shell,
							t_redirects *current);
int						break_here_doc(t_redirects *current, char *line);
void					handle_signal_here_doc(int sig);
void					close_pipes(int *pipe_in, int *fd, t_cmd *current);
void					setup_fd(t_shell *shell, t_cmd *current, int *fd);
int						check_here_docs(t_cmd *cmd, t_shell *shell);
void					redirect_input(t_cmd *cmd, t_shell *shell, int pipe_in);
void					redirect_output(t_cmd *cmd, t_shell *shell);
void					process(t_cmd *cmd, t_shell *shell, int pipe_in,
							int *fd);
void					wait_for_child(t_shell *shell);
void					handle_error_file(t_cmd *cmd, t_shell *shell,
							char **envp);
void					handle_error_execve(t_cmd *cmd, t_shell *shell,
							char **envp, int exit_error);
void					handle_error_process(t_cmd *cmd, t_shell *shell,
							char **envp, int exit_error);
char					*get_cmd_path(const char *cmd, char **envp);
void					exec_builtins(t_shell *shell, t_cmd *cmd);

// builtins
int						is_builtins(t_cmd *cmd);
int						is_parent_builtins(t_cmd *cmd);
void					builtin_echo(t_shell *shell, t_cmd *cmd);
void					builtin_cd(t_shell *shell, t_cmd *cmd);
void					builtin_pwd(t_shell *shell, t_cmd *cmd);
void					builtin_export(t_shell *shell, t_cmd *cmd);
void					builtin_unset(t_shell *shell, t_cmd *cmd);
void					builtin_env(t_shell *shell, t_cmd *cmd);
void					builtin_exit(t_shell *shell, t_cmd *cmd);

// main
void					setup_signals(int is_parent);
t_cmd					*parse_input(const char *input, t_shell *shell);
void					exec_cmd(t_cmd *cmd, t_shell *shell);
extern int				g_signal;
#endif
