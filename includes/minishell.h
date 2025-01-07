/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:02:01 by ltheveni          #+#    #+#             */
/*   Updated: 2025/01/07 14:07:07 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "ft_printf.h"
# include "libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/wait.h>

typedef struct s_cmd
{
	char			**args;
	struct s_cmd	*next;
}					t_cmd;

t_cmd				*parse_input(char *input);
void				exec_cmd(t_cmd *cmd);
#endif
