/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 13:18:34 by rpinoit           #+#    #+#             */
/*   Updated: 2018/10/11 14:58:39 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

# define ERROR_READ "Error while reading the prompt\n"
# define ERROR_MALLOC "Error while trying to malloc\n"

typedef struct  s_shell
{
    char        **env;
    char        *cmd;
    int         end;
}               t_shell;

void    print_error(char *error);
void    malloc_error();

#endif