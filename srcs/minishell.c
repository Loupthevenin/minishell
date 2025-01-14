/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kleung-t <kleung-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:01:37 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/14 11:02:29 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// compile : gcc minishell.c -lreadline

#include "../includes/minishell.h"

static void	init_shell(t_shell *shell, char **envp)
{
	shell->env = envp;
	shell->pid = -1;
	shell->n_pipes = 0;
	shell->last_exit = 0;
}

static void	clean_shell(t_cmd *cmd, t_shell *shell)
{
	free_cmd_node(cmd);
	free_tab((void **)shell->pipefd, shell->n_pipes, 0);
	/* free_tab((void **)shell->env, 0, 1); */
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_cmd	*cmd;
	t_shell	shell;

	(void)argc;
	(void)argv;
	init_shell(&shell, envp);
	setup_signals(1);
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		cmd = parse_input(input);
		exec_cmd(cmd, &shell);
		free(input);
	}
	clean_shell(cmd, &shell);
	return (0);
}
