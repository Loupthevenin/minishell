/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kleung-t <kleung-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:01:37 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/27 10:36:53 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// compile : gcc minishell.c -lreadline

#include "../includes/minishell.h"

static void	init_shell(t_shell *shell, char **envp)
{
	if (envp && *envp)
		shell->env_list = double_array_to_list(envp);
	else
		shell->env_list = add_default_env_vars();
	shell->pid = -1;
	shell->n_pipes = 0;
	shell->last_exit = 0;
	update_shlvl(shell);
}

static void	clean_shell(t_cmd *cmd, t_shell *shell)
{
	if (cmd)
		free_cmd_node(cmd);
	if (shell)
		free_shell(shell);
	rl_clear_history();
}

static void	handle_main_loop(t_shell *shell, t_cmd *cmd, char *input)
{
	add_history(input);
	if (g_signal == SIGINT)
	{
		shell->last_exit = 130;
		g_signal = 0;
	}
	cmd = parse_input(input, shell);
	free(input);
	exec_cmd(cmd, shell);
	free_cmd_node(cmd);
	cmd = NULL;
}

static void	main_loop(t_shell *shell)
{
	char	*input;
	t_cmd	*cmd;

	cmd = NULL;
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (*input == '\0')
		{
			free(input);
			continue ;
		}
		handle_main_loop(shell, cmd, input);
	}
	clean_shell(cmd, shell);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	init_shell(&shell, envp);
	setup_signals(1);
	main_loop(&shell);
	return (0);
}
