/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_binaries.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 13:34:35 by rpinoit           #+#    #+#             */
/*   Updated: 2018/10/25 15:21:44 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*new_path(const char *start, const char *end)
{
	char *new;
	char *ret;

	if (start == NULL)
		return (ft_strdup(end));
	if ((new = (char *)malloc(sizeof(char)
					* (ft_strlen(start) + ft_strlen(end) + 2))) == NULL)
		malloc_error();
	ret = new;
	while (*start != '\0')
		*new++ = *start++;
	*new++ = '/';
	while (*end != '\0')
		*new++ = *end++;
	*new = '\0';
	return (ret);
}

static char	*search_bin_path(const char *env_path, const char *bin)
{
	struct stat	st;
	char		**all;
	char		*path;
	int			i;

	ft_bzero(&st, sizeof(struct stat));
	if (stat(bin, &st) != 1 && S_ISREG(st.st_mode))
		return (ft_strdup(bin));
	i = 0;
	all = ft_strsplit(env_path, ':');
	while (all != NULL && all[i] != NULL)
	{
		path = new_path(all[i], bin);
		if (stat(path, &st) != 1 && S_ISREG(st.st_mode))
		{
			ft_deltab(all, 0);
			return (path);
		}
		ft_strdel(&path);
		++i;
	}
	ft_deltab(all, 0);
	return (NULL);
}

int			execute_binaries(const char **args)
{
	char	*env_path;
	char	*bin_path;
	pid_t	forkid;

	env_path = env_search("PATH=");
	if ((bin_path = search_bin_path(env_path, args[0])) == NULL)
		return (0);
	if (access(bin_path, X_OK) == -1)
	{
		print_error(ERROR_EXECUTION);
		return (1);
	}
	forkid = fork();
	if (forkid > 0)
	{
		wait(0);
		ft_strdel(&bin_path);
	}
	else if (forkid == 0)
	{
		execve(bin_path, (char **)args, shell_singletone()->env);
	}
	return (1);
}
