/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 13:20:33 by rpinoit           #+#    #+#             */
/*   Updated: 2018/10/23 14:16:52 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    display_prompt(int error)
{
    char cdw[256];

    if (error == 1)
        write(1, "✗ ", 4);
    else
        write(1, "✔ ", 4);
    if (getcwd(cdw, 256) != NULL)
        ft_putstr(cdw);
    write(1, " $> ", 3);
}

void    read_cmdline(char **line, int *end)
{
    int     ret;

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

char    *get_dollar_value(char *str)
{
    char    *val;
    int     i;

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

void    env_rm(char *var, int var_len)
{
    char    ***env;
    char    **tmp_env;
    char    **new_env;
    int     len;
    int     i;
    int     j;

    env = &shell_singletone()->env;
    tmp_env = *env;
    len = ft_tablen(tmp_env);
    if ((new_env = (char **)malloc(sizeof(char *) * (len - 1))) == NULL)
        malloc_error();
    i = 0;
    j = 0;
    while (tmp_env[i] != NULL)
    {
        if (ft_strncmp(tmp_env[i], var, var_len) == 0)
            ;
        else
            new_env[j] = tmp_env[i];
        j++;
        i++;
    }
    new_env[len - 1] = NULL;
    ft_deltab(tmp_env, 0);
    env = &new_env;
}

void    env_add(char *new_var)
{
    char    ***env;
    char    **tmp_env;
    char    **new_env;
    int     len;

    env = &shell_singletone()->env;
    tmp_env = *env;
    len = ft_tablen(tmp_env);
    if ((new_env = (char **)malloc(sizeof(char *) * (len + 1))) == NULL)
        malloc_error();
    ft_memcpy((void *)new_env, (void *)tmp_env, sizeof(char *) * (len - 1));
    new_env[len - 1] = new_var;
    new_env[len] = NULL;
    ft_deltab(tmp_env, 0);
    env = &new_env;
}


char    *triple_join(char *begin, char *middle, char *end)
{
    char    *join;
    int     len1;
    int     len2;
    int     len3;

    len1 = ft_strlen(begin);
    len2 = ft_strlen(middle);
    len3 = ft_strlen(end);
    if ((join = (char *)malloc(sizeof(char) * (len1 + len2 + len3 + 1))) == NULL)
        malloc_error();
    ft_memcpy(join, begin, len1);
    ft_memcpy(join + len1, middle, len2);
    ft_memcpy(join + len1 + len2, end, len3);
    join[len1 + len2 + len3] = '\0';
    ft_strdel(&begin);
    ft_strdel(&middle);
    ft_strdel(&end);
    return (join);
}

char    *sandr_expansions(char *cmdline)
{
    ft_strdel(&cmdline);
    return (triple_join(ft_strdup("echo "), ft_strdup("/Users/rpinoit"), ft_strdup(" poulet")));
}

int     main(void)
{
	extern char **environ;
    t_shell     *shell;
    char        *line;

    shell = shell_singletone();
    shell->env = env_copy(environ);
    while (shell->end == 0)
    {
        display_prompt(shell->error);
        shell->error = 0;
        read_cmdline(&line, &shell->end);
        if (shell->end == 1)
            break ;
        shell->cmdline = line;
        execute_cmdline(shell->cmdline);
        shell_clear(shell);
    }
    shell_free(shell);
    write(1, "\n", 1);
    return (0);
}
