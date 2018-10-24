/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 17:21:20 by rpinoit           #+#    #+#             */
/*   Updated: 2018/10/24 17:32:00 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     ft_setenv(const char **args)
{
    char    *new;
    char    *tmp;

    if (args[1] == NULL)
        return (ft_env(args));
    else if (args[2] == NULL)
    {
        if (ft_strchr(args[1], '=') != NULL)
            env_add(args[1]);
    }
    else
    {
        tmp = ft_strjoin(args[1], "=");
        new = ft_strjoin(tmp, args[2]);
        env_add(new);
        ft_strdel(&tmp);
        ft_strdel(&new);
    }
    return (1);
}