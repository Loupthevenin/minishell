/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 18:29:17 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/31 13:14:55 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			g_signal = 0;

static void	handle_signal_parent(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = SIGINT;
		ft_putstr_fd("\n", 1);
		if (waitpid(-1, NULL, WNOHANG) == 0)
			return ;
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	setup_signals(int is_parent)
{
	if (is_parent)
	{
		signal(SIGINT, handle_signal_parent);
		signal(SIGQUIT, SIG_IGN);
	}
	else
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
}
