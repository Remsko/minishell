/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 22:43:50 by rpinoit           #+#    #+#             */
/*   Updated: 2018/10/25 15:39:11 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	new_exec(const char **args, unsigned char flags)
{
	t_shell *shell;
	char	**env;

	shell = shell_singletone();
	env = shell->env;
	if (flags & 0x1)
		shell->env = NULL;
	if (*args != NULL && args != NULL)
		execute_binaries(args);
	shell->env = env;
}

int			ft_env(const char **args)
{
	unsigned char flags;

	flags = 0;
	if (args[1] == NULL)
		ft_print_words_tables(shell_singletone()->env);
	else
	{
		while (*(++args) != NULL)
		{
			if (ft_strcmp(*args, "-i") == 0)
				flags |= 0x1;
			else
				break ;
		}
		new_exec(args, flags);
	}
	return (1);
}
