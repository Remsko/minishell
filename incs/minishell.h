/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 13:18:34 by rpinoit           #+#    #+#             */
/*   Updated: 2018/10/23 14:17:10 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <unistd.h>
//# include <stdio.h>

# define ERROR_READ "Error while reading the prompt\n"
# define ERROR_MALLOC "Error while trying to malloc\n"
# define ERROR_COMMAND "Error command not found: "

# define FLAG_N 0x1

typedef struct  s_shell
{
    char        **env;
    char        *cmdline;
    int         error;
    int         end;
}               t_shell;

t_shell *shell_singletone(void);
void    shell_clear(t_shell *shell);
void    shell_free(t_shell *shell);

void    print_error(const char *error);
void    malloc_error(void);
void    command_error(const char *arg);

void    execute_cmdline(char *cmdline);
int     execute_builtins(const char **args);
int     execute_binaries(const char **args);

int     ft_exit(void);
int     ft_echo(const char **args);
int     ft_cd(const char **args);

char    **env_copy(char **env);
char    *env_search(char *var);

#endif