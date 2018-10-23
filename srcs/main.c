/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 13:20:33 by rpinoit           #+#    #+#             */
/*   Updated: 2018/10/19 16:35:47 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell *shell_singletone(void)
{
    static t_shell *shell = NULL;

    if (shell == NULL)
    {
        if ((shell = (t_shell *)malloc(sizeof(t_shell))) == NULL)
            malloc_error();
        ft_bzero((void *)shell, sizeof(t_shell));
    }
    return (shell);
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

void    display_prompt()
{
    write(1, "$> ", 3);
}

void    clear_shell(t_shell *shell)
{
    ft_strdel(&shell->cmdline);
}

void    free_shell(t_shell *shell)
{
    ft_deltab(shell->env, 0);
    ft_memdel((void **)&shell);
}

char    *env_search(char *var)
{
    char    **env;
    int     len;
    int     i;

    i = 0;
    len = ft_strlen(var);
    env = shell_singletone()->env;
    while (env[i] != NULL)
    {
        if (ft_strncmp(env[i], var, len) == 0)
            return (env[i] + len + 1);
        ++i;
    }
    return (NULL);
}

int    execute_builtin(const char **args)
{
    if (ft_strcmp(args[0], "echo") == 0)
        return (ft_echo(args));
    else if (ft_strcmp(args[0], "cd") == 0)
        return (ft_cd(args));
    else if (ft_strcmp(args[0], "setenv") == 0)
        return (1);
    else if (ft_strcmp(args[0], "unsetenv") == 0)
        return (1);
    else if (ft_strcmp(args[0], "env") == 0)
        return (1);
    else if (ft_strcmp(args[0], "exit") == 0)
        return (ft_exit());
    return (0);
}

char    *new_path(const char *start, const char *end)
{
    char    *new;
    char    *ret;

    if (start == NULL)
        return (ft_strdup(end));
    if ((new = (char *)malloc(sizeof(char) * (ft_strlen(start)
                        + ft_strlen(end) + 2))) == NULL)
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

char    *search_bin_path(const char *env_path, const char *bin)
{
    struct stat st;
    char        **all;
    char        *path;
    int         i;

    if (env_path == NULL || bin == NULL)
        return (NULL);
    ft_bzero(&st, sizeof(struct stat));
    if (stat(bin, &st) != 1 && S_ISREG(st.st_mode))
            return (ft_strdup(bin));
    i = 0;
    all = ft_strsplit(env_path, ':');
    while (all[i] != NULL)
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

int     execute_binary(const char **args)
{
    char    *env_path;
    char    *bin_path;
    pid_t   forkid;

    env_path = env_search("PATH=");
    bin_path = search_bin_path(env_path, args[0]);
    if (bin_path == NULL)
        return (0);
    forkid = fork();
    if (forkid > 0)
    {
        wait(0);
        ft_strdel(&bin_path);
    }
    else if (forkid == 0)
    {
        execve(bin_path, (char **)args, NULL);
    }
    return (1);
}

void    handle_cmd(char *cmd)
{
    const char **args;

    args = (const char **)ft_split_whitespaces(cmd);
    if (args == NULL)
        return ;
    if (execute_builtin(args))
        ;
    else if (execute_binary(args))
        ;
    else
        command_error(args[0]);
    ft_deltab(args, 0);
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

void    execute_cmdline(char *cmdline)
{
    char    **split;
    int     i;

    i = 0;
    split = ft_strsplit(cmdline, ';');
    if (split == NULL)
        return ;
    while (split[i] != NULL)
    {
        handle_cmd(split[i]);
        ++i;
    }
    ft_deltab(split, 0);
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
    t_shell *shell;
    char    *line;

	extern char **environ;
    shell = shell_singletone();
    shell->env = env_copy(environ);
    while (shell->end == 0)
    {
        display_prompt();
        read_cmdline(&line, &shell->end);
        if (shell->end == 1)
            break ;
        shell->cmdline = line;
        execute_cmdline(shell->cmdline);
        clear_shell(shell);
    }
    free_shell(shell);
    ft_putendl("");
    return (0);
}
