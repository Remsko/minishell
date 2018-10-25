/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_rm.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 11:27:51 by rpinoit           #+#    #+#             */
/*   Updated: 2018/10/25 11:28:26 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void env_rm(char *var, int var_len)
{
    t_shell *shell;
    char **new_env;
    int len;
    int i;

    shell = shell_singletone();
    len = ft_tablen(shell->env);
    if ((new_env = (char **)malloc(sizeof(char *) * len)) == NULL)
        malloc_error();
    new_env[len - 1] = NULL;
    i = len - 2;
    while (len-- > 0)
    {
        if (ft_strncmp(shell->env[len], var, var_len) == 0)
            ft_strdel(&shell->env[len]);
        else
        {
            new_env[i] = shell->env[len];
            --i;
        }
    }
    ft_memdel((void **)&shell->env);
    shell->env = new_env;
}