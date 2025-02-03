/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal_here_doc.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:08:45 by ltheveni          #+#    #+#             */
/*   Updated: 2025/02/03 09:11:20 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	handle_signal_here_doc(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = SIGINT;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
	}
}
