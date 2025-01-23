/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 21:15:12 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/23 21:15:31 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	is_quote(char c, t_split *state)
{
	if (c == '\'' && !(state->in_double_quote))
		state->in_single_quote = !(state->in_single_quote);
	else if (c == '"' && !(state->in_double_quote))
		state->in_double_quote = !(state->in_double_quote);
	return (state->in_single_quote || state->in_double_quote);
}
