/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 13:38:34 by rpinoit           #+#    #+#             */
/*   Updated: 2018/10/24 16:55:33 by rpinoit          ###   ########.fr       */
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

int ft_unsetenv(const char **args)
{
    char *var;
    char *tmp;

    if (args[1] == NULL)
        print_error(ERROR_ARG);
    else
    {
        while (*(++args) != NULL)
        {
            tmp = ft_strdup(*args);
            var = ft_strjoin(tmp, "=");
            if (env_search(var) != NULL)
                env_rm(var, ft_strlen(var));
            ft_strdel(&tmp);
            ft_strdel(&var);
        }
    }
    return (1);
}