/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmdline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 13:27:10 by rpinoit           #+#    #+#             */
/*   Updated: 2018/10/25 15:32:55 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_cmd(char *cmd)
{
	const char **args;

	args = (const char **)ft_split_whitespaces(cmd);
	if (args == NULL)
		return ;
	if (*args != NULL)
	{
		if (execute_builtins(args))
			;
		else if (execute_binaries(args))
			;
		else
			command_error(args[0]);
	}
	ft_deltab(args, 0);
}

void		execute_cmdline(char *cmdline)
{
	char	**split;
	int		i;

	i = 0;
	split = ft_strsplit(cmdline, ';');
	if (split == NULL)
		return ;
	while (split[i] != NULL)
	{
		handle_cmd(split[i]);
		++i;
	}
	ft_deltab(split, 0);
}
