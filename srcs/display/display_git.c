/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_git.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 11:50:32 by rpinoit           #+#    #+#             */
/*   Updated: 2018/10/25 14:36:05 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	display_branch(int fd, char *buf)
{
	int ret;

	if ((ret = read(fd, buf, 256)) > 5)
	{
		if (buf[ret - 1] == '\n')
			buf[ret - 1] = '\0';
		else
			buf[ret] = '\0';
		if (ft_strncmp(buf, "refs/", 5) == 0)
		{
			ft_putstr(" git:(");
			(ft_strncmp(buf, "heads/", 6) != 0)
				? ft_putstr(buf + 11)
				: ft_putstr(buf + 5);
			ft_putstr(")");
		}
	}
	close(fd);
}

void		display_git(char *cwd)
{
	char	buf[256 + 1];
	char	*pos;
	int		fd;

	ft_strcat(cwd, "/");
	pos = ft_strrchr(cwd, '/');
	while (cwd + 1 < pos)
	{
		if ((pos = ft_strrchr(cwd, '/')) == NULL)
			return ;
		*pos = '\0';
		ft_strcat(pos, "/.git/HEAD");
		if ((fd = open(cwd, O_RDONLY)) > 0)
		{
			if (read(fd, buf, 5) == 5)
				return (display_branch(fd, buf));
			close(fd);
		}
		*pos = '\0';
	}
}
