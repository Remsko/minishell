/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 11:25:51 by rpinoit           #+#    #+#             */
/*   Updated: 2018/10/25 14:37:18 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_add(char **var)
{
	t_shell	*shell;
	char	**new_env;
	int		len;

	shell = shell_singletone();
	len = ft_tablen(shell->env);
	if ((new_env = (char **)malloc(sizeof(char *) * (len + 2))) == NULL)
		malloc_error();
	new_env[len + 1] = NULL;
	new_env[len] = *var;
	while (len-- > 0)
		new_env[len] = shell->env[len];
	ft_memdel((void **)&shell->env);
	shell->env = new_env;
}
