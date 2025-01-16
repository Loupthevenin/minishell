/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kleung-t <kleung-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:01:37 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/16 16:05:01 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// compile : gcc minishell.c -lreadline

#include "../includes/minishell.h"

static void	init_shell(t_shell *shell, char **envp)
{
	if (envp)
		shell->env_list = double_array_to_list(envp);
	else
	{
		shell->env_list = NULL;
	}
	shell->pid = -1;
	shell->n_pipes = 0;
	shell->last_exit = 0;
}

static void	clean_shell(t_cmd *cmd, t_shell *shell)
{
	if (cmd)
		free_cmd_node(cmd);
	if (shell)
		free_shell(shell);
	rl_clear_history();
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
		cmd = parse_input(input);
		free(input);
		exec_cmd(cmd, shell);
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
