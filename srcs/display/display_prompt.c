/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 11:40:29 by rpinoit           #+#    #+#             */
/*   Updated: 2018/10/25 11:52:08 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void display_prompt(int error)
{
    char cdw[256 + 1];

    if (error == 1)
        write(1, "\u2717 ", 4);
    else
        write(1, "\u2713 ", 4);
    if (getcwd(cdw, 256) != NULL)
        display_path(cdw);
    display_git(cdw);
    write(1, " $> ", 3);
}