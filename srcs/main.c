/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 13:20:33 by rpinoit           #+#    #+#             */
/*   Updated: 2018/10/25 13:54:42 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void read_cmdline(char **line, int *end)
{
    int ret;

    while ((ret = get_next_line(0, line)) != 1)
    {
        if (ret == -1)
        {
            print_error(ERROR_READ);
            break ;
        }
        else if (ret == 0)
        {
            *end = 1;
            break ;
        }
    }
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
            break ;
        shell->cmdline = expansion_sandr(line);
        execute_cmdline(shell->cmdline);
        shell_clear(shell);
    }
    shell_free(shell);
    write(1, "\n", 1);
    return (0);
}
