/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_search.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 13:41:23 by rpinoit           #+#    #+#             */
/*   Updated: 2018/10/23 13:43:14 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *env_search(char *var)
{
    char **env;
    int len;
    int i;

    i = 0;
    len = ft_strlen(var);
    env = shell_singletone()->env;
    while (env[i] != NULL)
    {
        if (ft_strncmp(env[i], var, len) == 0)
            return (env[i] + len + 1);
        ++i;
    }
    return (NULL);
}