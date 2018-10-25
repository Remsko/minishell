/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 13:38:34 by rpinoit           #+#    #+#             */
/*   Updated: 2018/10/25 14:34:05 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unsetenv(const char **args)
{
	char	*var;
	char	*tmp;

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
