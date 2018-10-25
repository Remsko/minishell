/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 13:18:34 by rpinoit           #+#    #+#             */
/*   Updated: 2018/10/25 14:31:45 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

# define ERROR_READ "Error while reading the prompt\n"
# define ERROR_MALLOC "Error while trying to malloc\n"
# define ERROR_COMMAND "Error minishell: command not found: "
# define ERROR_GETCWD "Error cd: fail to get the absolute path\n"
# define ERROR_PERMISSION "Error cd: permission denied: "
# define ERROR_DIRECTORY "Error cd: no such file or directory: "
# define ERROR_ANY "Error cd: not a directory: "
# define ERROR_ARG "Error unsetenv: not enough arguments\n"
# define ERROR_EXECUTION "Error: permission denied\n"

# define FLAG_N 0x1

typedef struct	s_shell
{
	char		**env;
	char		*cmdline;
	int			error;
	int			end;
}				t_shell;

t_shell			*shell_singletone(void);
void			shell_clear(t_shell *shell);
void			shell_free(t_shell *shell);

void			print_error(const char *error);
void			malloc_error(void);
void			command_error(const char *arg);

void			execute_cmdline(char *cmdline);
int				execute_builtins(const char **args);
int				execute_binaries(const char **args);

int				ft_exit(void);
int				ft_echo(const char **args);
int				ft_cd(const char **args);
int				ft_unsetenv(const char **args);
int				ft_setenv(const char **args);
int				ft_env(const char **args);

char			**env_copy(char **env);
char			*env_search(char *var);
void			env_change(char **new, char *var);
void			env_add(char **var);
void			env_rm(char *var, int var_len);

void			display_prompt(int error);
void			display_git(char *cwd);
void			display_path(char *cwd);

char			*expansion_sandr(char *cmdline);

#endif
