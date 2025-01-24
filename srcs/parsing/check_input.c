/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:27:28 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/24 14:34:25 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// GESTION DE TOUTES LES ERREURS ATTENTION ON DOIT free_shell(shell) AVANT D'EXIT
//	+ shell.last_exit = numero_d'error :
// >>>> : "minishell: syntax error near unexpected token `>>`"
// > > > > : "minishell: syntax error near unexpected token `>`"
// > : "minishell: syntax error near unexpected token `newline`"
// / : "minishell: /: Is a directory"
// // : "minishell: //: Is a directory"
void	check_input(const char *input, t_shell *shell)
{
	(void)input;
	(void)shell;
}
