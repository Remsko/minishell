/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_singletone.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 13:49:30 by rpinoit           #+#    #+#             */
/*   Updated: 2018/10/25 14:46:58 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	*shell_singletone(void)
{
	static t_shell *shell = NULL;

	if (shell == NULL)
	{
		if ((shell = (t_shell *)malloc(sizeof(t_shell))) == NULL)
			malloc_error();
		ft_bzero((void *)shell, sizeof(t_shell));
	}
	return (shell);
}
