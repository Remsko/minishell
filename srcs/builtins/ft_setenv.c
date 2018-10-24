/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 17:21:20 by rpinoit           #+#    #+#             */
/*   Updated: 2018/10/24 22:43:33 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>
void env_add(char **var)
{
    t_shell *shell;
    char **new_env;
    int len;

    shell = shell_singletone();
    len = ft_tablen(shell->env);
    if ((new_env = (char **)malloc(sizeof(char *) * (len + 2))) == NULL)
        malloc_error();
    new_env[len + 1] = NULL;
    new_env[len] = *var;
    ft_memcpy((void *)new_env, (void *)shell->env, sizeof(char *) * (len - 1));
    ft_memdel((void **)&shell->env);
    shell->env = new_env;
}

int ft_setenv(const char **args)
{
    char *new;
    char *tmp;

    if (args[1] == NULL)
        //return (ft_env(args));
        return (1);
    else if (args[2] == NULL)
    {
        if ((tmp = ft_strchr(args[1], '=')) != NULL)
        {
            tmp = ft_strndup(args[1], tmp - new),
            new = ft_strdup(args[1]);
            if (env_search(tmp) == NULL)
                env_add(&new);
            else
                env_change(&new, tmp);
            ft_strdel(&tmp);
        }
    }
    else
    {
        tmp = ft_strjoin(args[1], "=");
        new = ft_strjoin(tmp, args[2]);
        if (env_search(tmp) == NULL)
            env_add(&new);
        else
            env_change(&new, tmp);
        ft_strdel(&tmp);
    }
    return (1);
}