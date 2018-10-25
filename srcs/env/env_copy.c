/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_copy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 13:41:30 by rpinoit           #+#    #+#             */
/*   Updated: 2018/10/25 14:38:02 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**env_copy(char **env)
{
	char	**new_env;
	int		tab_len;

	tab_len = ft_tablen(env);
	if ((new_env = (char **)malloc(sizeof(char *) * (tab_len + 1))) == NULL)
		malloc_error();
	new_env[tab_len] = NULL;
	while (tab_len-- > 0)
		new_env[tab_len] = ft_strdup(env[tab_len]);
	return (new_env);
}
