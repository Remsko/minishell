/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 13:20:33 by rpinoit           #+#    #+#             */
/*   Updated: 2018/10/11 15:59:47 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    read_cmdline(t_shell *shell)
{
    char    *line;
    int     ret;

    while ((ret = get_next_line(0, &line)) != 1)
    {
        if (ret == -1)
        {
            print_error(ERROR_READ);
            break ;
        }
        else if (ret == 0)
        {
            shell->end = 1;
            break ;
        }
    }
    shell->cmd = line;
}

void    display_prompt()
{
    write(1, "$> ", 3);
}

void    clear_shell(t_shell *shell)
{
    ft_strdel(&shell->cmd);
}

void    execute_cmd(char *cmd)
{
    char **args;

    args = ft_split_whitespaces(cmd);
    ft_print_words_tables(args);
    ft_deltab(args, 0);
}

void    execute_cmdline(t_shell *shell)
{
    char    **split;
    int     i;

    i = 0;
    split = ft_strsplit(shell->cmd, ';');
    while (split[i] != NULL)
    {
        execute_cmd(split[i]);
        //ft_putendl(split[i]);
        ++i;
    }
    ft_deltab(split, 0);
}

char    **env_copy(char **env)
{
    char    **new_env;
    int     tab_len;
    int     i;

    tab_len = ft_tablen(env);
    if ((new_env = (char **)malloc(sizeof(char *) * (tab_len + 1))) == NULL)
        malloc_error();
    i = 0;
    while (i < tab_len)
    {
        new_env[i] = ft_strdup(env[i]);
        ++i;
    }
    new_env[i] = NULL;
    return (new_env);
}

int main(int argc, char **argv, char **env)
{
    t_shell shell;

    (void)argc;
    (void)argv;
    ft_bzero((void *)&shell, sizeof(t_shell));
    shell.env = env_copy(env);
    while (shell.end == 0)
    {
        display_prompt();
        read_cmdline(&shell);
        if (shell.end == 1)
            break ;
        execute_cmdline(&shell);
        clear_shell(&shell);
    }
    ft_deltab(shell.env, 0);
    return (0);
}