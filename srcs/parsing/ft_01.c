/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_01.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kleung-t <kleung-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 18:24:36 by kleung-t          #+#    #+#             */
/*   Updated: 2025/01/27 17:46:51 by kleung-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	if_op(const char *s)
{
	if (!s || !*s)
		return (0);
	if (!ft_strncmp(s, "<<", 2) || !ft_strncmp(s, ">>", 2))
		return (1);
	if (*s == '<' || *s == '>')
		return (1);
	return (0);
}

int	ft_sp(char c)
{
	if ((c >= 7 && c <= 13) || c == 32 || c == 0)
		return (1);
	else
		return (0);
}
