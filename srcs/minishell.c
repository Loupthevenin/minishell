/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kleung-t <kleung-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:01:37 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/14 02:42:38 by kleung-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// compile : gcc minishell.c -lreadline

#include "../includes/minishell.h"
#include "./parsing/parser.c"

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
	char		*input;
	t_cmd		**args;
	t_cmd		*cmd;
	t_shell	shell;
	t_token	**token;
	int		i;
	int		j;

	i = 0;
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
		// cmd = parse_input(input);
		t_cmd->args = split_input(input);
		while (t_cmd->args[i])
		{
			t_token->token = split_arg(t_cmd->args[i++]);
			j = 0;
			while (t_token->token[j])
				printf("token %d : [%s]\n", j, t_token->token[j++]);
		}
		// exec_cmd(cmd, shell);
		free(input);
	}
	clean_shell(cmd, &shell);
	return (0);
}
