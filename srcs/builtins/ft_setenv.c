/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 17:21:20 by rpinoit           #+#    #+#             */
/*   Updated: 2018/10/25 11:30:05 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_setenv(const char **args)
{
    char *new;
    char *tmp;

    if (args[1] == NULL)
        return (ft_env(args));
    else if (args[2] == NULL)
    {
        if ((tmp = ft_strchr(args[1], '=')) != NULL)
        {
            tmp = ft_strndup(args[1], tmp - args[1]);
            new = ft_strdup(args[1]);
            (env_search(tmp) == NULL) ? env_add(&new) : env_change(&new, tmp);
            ft_strdel(&tmp);
        }
    }
    else
    {
        tmp = ft_strjoin(args[1], "=");
        new = ft_strjoin(tmp, args[2]);
        (env_search(tmp) == NULL) ? env_add(&new) : env_change(&new, tmp);
        ft_strdel(&tmp);
    }
    return (1);
}