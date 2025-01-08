/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kleung-t <kleung-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:01:37 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/08 10:26:00 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// compile : gcc minishell.c -lreadline

#include "../includes/minishell.h"
#include "./parsing/parser.c"

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_cmd	*cmd;

	(void)argc;
	(void)argv;
	(void)envp;
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		// cmd = parse_input(input);
		split_arg(input);
		// exec_cmd(cmd, envp);
		free(input);
	}
	return (0);
}
