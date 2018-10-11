/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 13:18:34 by rpinoit           #+#    #+#             */
/*   Updated: 2018/10/11 16:32:29 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <unistd.h>

# define ERROR_READ "Error while reading the prompt\n"
# define ERROR_MALLOC "Error while trying to malloc\n"
# define ERROR_COMMAND "Error command not found: "

typedef struct  s_shell
{
    char        **env;
    char        *cmd;
    int         end;
}               t_shell;

void    print_error(const char *error);
void    malloc_error(void);
void    command_error(const char *arg);

#endif