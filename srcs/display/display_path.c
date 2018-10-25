/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 11:50:44 by rpinoit           #+#    #+#             */
/*   Updated: 2018/10/25 11:51:27 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void display_path(char *cwd)
{
    char *pos;

    if (ft_strcmp(cwd + 1, env_search("HOME=")) == 0)
    {
        ft_putstr("~");
        return;
    }
    if (ft_strrchr(ft_strchr(cwd, '/'), '/') == cwd)
        pos = cwd;
    else
        pos = ft_strrchr(cwd, '/') + 1;
    ft_putstr(pos);
}