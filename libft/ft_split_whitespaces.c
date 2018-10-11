/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_whitespaces.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 15:53:00 by rpinoit           #+#    #+#             */
/*   Updated: 2018/10/11 15:55:21 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int     ft_count_words2(char const *s)
{
	int count;
	int get_count;

	count = 0;
	get_count = 0;
	while (*s != '\0')
	{
		if (get_count == 1 && ft_isspace(*s))
			get_count = 0;
		if (get_count == 0 && ft_isspace(*s) == 0)
		{
			get_count = 1;
			++count;
		}
		++s;
	}
	return (count);
}

char	**ft_split_whitespaces(char const *s)
{
	size_t		len;
	char		**tab;
	char		**ret;

	if (!s || !(tab = (char**)malloc(sizeof(*tab) * \
					(ft_count_words2(s) + 1))))
		return (NULL);
	ret = tab;
	while (*s)
	{
		if (ft_isspace(*s))
			++s;
		else
		{
			len = 0;
			while (*(s + len) && ft_isspace(*(s + len)) == 0)
				++len;
			if (!(*tab++ = ft_strndup(s, len)))
				return (NULL);
			s += len;
		}
	}
	tab[0] = NULL;
	return (ret);
}
