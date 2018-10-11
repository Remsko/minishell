/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 14:14:02 by rpinoit           #+#    #+#             */
/*   Updated: 2018/10/11 14:57:59 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    print_error(char *error)
{
    ft_putendl(error);
}

void    malloc_error()
{
    print_error(ERROR_MALLOC);
    exit(EXIT_FAILURE);
}