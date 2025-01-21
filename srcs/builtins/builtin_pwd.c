/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:48:02 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/21 10:53:02 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin_pwd(t_shell *shell, t_cmd *cmd)
{
	char	*pwd;

	(void)cmd;
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		perror("pwd");
		shell->last_exit = EXIT_FAILURE;
		return ;
	}
	printf("%s\n", pwd);
	free(pwd);
	shell->last_exit = 0;
}
