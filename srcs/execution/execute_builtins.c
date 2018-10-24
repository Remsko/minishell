/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 13:30:51 by rpinoit           #+#    #+#             */
/*   Updated: 2018/10/24 22:45:51 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    execute_builtins(const char **args)
{
    if (ft_strcmp(args[0], "echo") == 0)
        return (ft_echo(args));
    else if (ft_strcmp(args[0], "cd") == 0)
        return (ft_cd(args));
    else if (ft_strcmp(args[0], "setenv") == 0)
        return (ft_setenv(args));
    else if (ft_strcmp(args[0], "unsetenv") == 0)
        return (ft_unsetenv(args));
    else if (ft_strcmp(args[0], "env") == 0)
        return (ft_env(args));
    else if (ft_strcmp(args[0], "exit") == 0)
        return (ft_exit());
    return (0);
}