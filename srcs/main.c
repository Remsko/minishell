/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 13:20:33 by rpinoit           #+#    #+#             */
/*   Updated: 2018/10/13 21:39:56 by rpinoit          ###   ########.fr       */
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

char    *read_cmdline(int *end)
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
            *end = 1;
            break ;
        }
    }
    return (line);
}

void    display_prompt()
{
    write(1, "$> ", 3);
}

void    clear_shell(t_shell *shell)
{
    ft_strdel(&shell->cmdline);
}

char    *ft_getenv(char *var)
{
    char    **env;
    int     len;
    int     i;

    i = 0;
    len = ft_strlen(var);
    env = shell_singletone()->env;
    while (env[i] != NULL)
    {
        /* forbidden function */
        if (strncmp(env[i], var, len) == 0)
            return (env[i] + len);
        ++i;
    }
    return (NULL);
}

int    execute_builtin(const char **args)
{
    if (ft_strcmp(args[0], "echo") == 0)
        return (ft_echo(args));
    else if (ft_strcmp(args[0], "cd") == 0)
        return (1);
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

    i = 0;
    if (env_path == NULL || bin == NULL)
        return (NULL);
    if (stat(bin, &st) != 1 && S_ISREG(st.st_mode))
        return (ft_strdup(bin));
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

    env_path = ft_getenv("PATH=\0");
    bin_path = search_bin_path(env_path, args[0]);
    if (bin_path == NULL)
        return (0);
    forkid = fork();
    if (forkid > 0)
    {
        //wait(0);
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
        /* forbidden function */
        if (strncmp(tmp_env[i], var, var_len) == 0)
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

int     main(int argc, char **argv, char **env)
{
    t_shell *shell;

    (void)argc;
    (void)argv;
    shell = shell_singletone();
    shell->env = env_copy(env);
    while (shell->end == 0)
    {
        display_prompt();
        shell->cmdline = read_cmdline(&shell->end);
        if (shell->end == 1)
            break ;
        execute_cmdline(shell->cmdline);
        clear_shell(shell);
    }
    ft_deltab(shell->env, 0);
    ft_memdel((void **)&shell);
    return (0);
}