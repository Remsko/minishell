/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 14:14:02 by rpinoit           #+#    #+#             */
/*   Updated: 2018/10/11 16:20:57 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    print_error(const char *error)
{
    ft_putstr(error);
}

void    malloc_error(void)
{
    print_error(ERROR_MALLOC);
    exit(EXIT_FAILURE);
}

void    command_error(const char *arg)
{
    print_error(ERROR_COMMAND);
    ft_putendl(arg);
}