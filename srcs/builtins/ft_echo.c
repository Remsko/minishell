/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 11:06:23 by rpinoit           #+#    #+#             */
/*   Updated: 2018/10/14 09:41:04 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void     ft_putarg(const char *arg)
{
    int len;

    len = ft_strlen(arg);
    if (arg[0] == '\"' && arg[len - 1] == '\"')
        write(1, arg + 1, len - 2);
    else
        write(1, arg, len);
}

int             ft_echo(const char **args)
{
    unsigned char flags;

    flags = 0;
    while (*(++args) != NULL)
    {
        if (ft_strcmp(*args, "-n") == 0)
            flags |= FLAG_N;
        else
            break ;
    }
    if (*args != NULL)
    {
        while (1)
        {
            ft_putarg(*args);
            if (*(++args) != NULL)
                write(1, " ", 1);
            else
                break ;
        }
    }
    if ((flags & FLAG_N) == 0)
        write(1, "\n", 1);
    return (1);
}