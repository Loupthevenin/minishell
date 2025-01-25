/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_shlvl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 20:00:52 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/25 20:09:30 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	update_shlvl(t_shell *shell)
{
	int		shlvl_value;
	char	*new_shlvl;
	char	*current_shlvl;

	current_shlvl = get_value_env(shell->env_list, "SHLVL");
	if (!current_shlvl)
		return ;
	shlvl_value = ft_atoi(current_shlvl);
	if (shlvl_value < 0)
		shlvl_value = 0;
	new_shlvl = ft_itoa(shlvl_value + 1);
	update_env_var(shell->env_list, "SHLVL", new_shlvl);
	free(new_shlvl);
}
