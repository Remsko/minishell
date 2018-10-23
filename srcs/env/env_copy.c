/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_copy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 13:41:30 by rpinoit           #+#    #+#             */
/*   Updated: 2018/10/23 13:41:48 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    **env_copy(char **env)
{
    char    **new_env;
    int     tab_len;
    int     i;

    tab_len = ft_tablen(env);
    if ((new_env = (char **)malloc(sizeof(char *) * (tab_len + 1))) == NULL)
        malloc_error();
    i = 0;
    while (i < tab_len)
    {
        new_env[i] = ft_strdup(env[i]);
        ++i;
    }
    new_env[i] = NULL;
    return (new_env);
}