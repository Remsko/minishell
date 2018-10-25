/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 11:50:44 by rpinoit           #+#    #+#             */
/*   Updated: 2018/10/25 14:52:16 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_path(char *cwd)
{
	char *pos;
	char *home;

	if ((home = env_search("HOME=")) != NULL)
	{
		if (ft_strcmp(cwd + 1, home) == 0)
		{
			ft_putstr("~");
			return ;
		}
	}
	if (ft_strrchr(ft_strchr(cwd, '/'), '/') == cwd)
		pos = cwd;
	else
		pos = ft_strrchr(cwd, '/') + 1;
	ft_putstr(pos);
}
