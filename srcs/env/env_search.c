/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_search.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 13:41:23 by rpinoit           #+#    #+#             */
/*   Updated: 2018/10/25 15:34:31 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*env_search(char *var)
{
	char	**env;
	int		len;
	int		i;

	if (var == NULL)
		return (NULL);
	i = 0;
	len = ft_strlen(var);
	if ((env = shell_singletone()->env) == NULL)
		return (NULL);
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], var, len) == 0)
			return (env[i] + len);
		++i;
	}
	return (NULL);
}
