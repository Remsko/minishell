/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 13:47:06 by rpinoit           #+#    #+#             */
/*   Updated: 2018/10/23 22:36:31 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void change_directory(const char *target)
{
    char path[256 + 1];
    char *cwd;

    if ((cwd = getcwd(path, 256)) == NULL)
        return (print_error(ERROR_GETCWD));
    if (chdir(target) == 0)
        /*ft_setenv("OLDPWD", cwd)*/;
    else
    {
        if (access(target, F_OK) == -1)
            print_error(ERROR_DIRECTORY);
        else if (access(target, R_OK) == -1)
            print_error(ERROR_PERMISSION);
        else
            print_error(ERROR_ANY);
        ft_putendl(target);
    }
}

int ft_cd(const char **args)
{
    char *old;

    if (args[1] == NULL)
        change_directory(env_search("HOME="));
    else if (ft_strcmp(args[1], "-") == 0)
    {
        old = env_search("OLDPWD=");
        change_directory(old);
        ft_putendl(old);
    }
    else if (ft_strcmp(args[1], "--") == 0)
        change_directory(env_search("HOME="));
    else
        change_directory(args[1]);
    return (1);
}
