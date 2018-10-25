/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_sandr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 12:02:21 by rpinoit           #+#    #+#             */
/*   Updated: 2018/10/25 14:42:27 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_dollar_value(char *str)
{
	char	*val;
	int		i;

	i = 0;
	if (str == NULL || *str != '$')
		return (NULL);
	++str;
	while (str[i] != '\0' && ft_isspace(str[i]) == 0)
		++i;
	if ((val = (char *)malloc(sizeof(char) * (i + 2))) == NULL)
		malloc_error();
	ft_memcpy(val, str, i);
	val[i] = '=';
	val[i + 1] = '\0';
	return (val);
}

char	*replace_word(char *str, char *rm_ptr, char *replace, int rm_len)
{
	char	*new;
	int		c[4];

	c[0] = ft_strlen(str);
	c[1] = rm_ptr - str;
	c[2] = ft_strlen(replace);
	c[3] = c[0] + c[2] - rm_len;
	if ((new = malloc(sizeof(char) * (c[3] + 1))) == NULL)
		malloc_error();
	ft_memcpy(new, str, c[1]);
	ft_memcpy(&new[c[1]], replace, c[2]);
	ft_memcpy(&new[c[2] + c[1]], &rm_ptr[rm_len], c[3] - c[2] - c[1]);
	new[c[3]] = '\0';
	ft_strdel(&str);
	return (new);
}

char	*expansion_sandr(char *cmdline)
{
	char	*exp;
	char	*var;
	int		i;

	i = 0;
	while (cmdline[i] != '\0')
	{
		if (cmdline[i] == '$' || cmdline[i] == '~')
		{
			if (cmdline[i] == '$')
				exp = get_dollar_value(&cmdline[i]);
			else
				exp = ft_strdup("HOME=");
			if ((var = env_search(exp)) == NULL)
				var = "\0";
			cmdline = replace_word(cmdline, &cmdline[i], var,
					(cmdline[i] == '$') ? ft_strlen(exp) : 1);
			ft_strdel(&exp);
			i += ft_strlen(var);
		}
		else
			++i;
	}
	return (cmdline);
}
