/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_change.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 21:59:06 by rpinoit           #+#    #+#             */
/*   Updated: 2018/10/25 14:37:37 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_change(char **new, char *var)
{
	t_shell	*shell;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(var);
	shell = shell_singletone();
	while (shell->env[i] != NULL)
	{
		if (ft_strncmp(shell->env[i], var, len) == 0)
		{
			ft_strdel(&shell->env[i]);
			shell->env[i] = *new;
			return ;
		}
		++i;
	}
}
