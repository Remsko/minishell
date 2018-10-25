/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 13:20:33 by rpinoit           #+#    #+#             */
/*   Updated: 2018/10/25 11:51:43 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void read_cmdline(char **line, int *end)
{
    int ret;

    while ((ret = get_next_line(0, line)) != 1)
    {
        if (ret == -1)
        {
            print_error(ERROR_READ);
            break;
        }
        else if (ret == 0)
        {
            *end = 1;
            break;
        }
    }
}

char *get_dollar_value(char *str)
{
    char *val;
    int i;

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

int main(void)
{
    extern char **environ;
    t_shell *shell;
    char *line;

    shell = shell_singletone();
    shell->env = env_copy(environ);
    while (shell->end == 0)
    {
        display_prompt(shell->error);
        shell->error = 0;
        read_cmdline(&line, &shell->end);
        if (shell->end == 1)
            break;
        shell->cmdline = line;
        execute_cmdline(shell->cmdline);
        shell_clear(shell);
    }
    shell_free(shell);
    write(1, "\n", 1);
    return (0);
}
