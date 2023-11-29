#ifndef MINISHEEL_H
# define MINISHELL_H

# include <stdio.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <limits.h>

typedef struct s_data
{
	int		err;
	int		exit;
	char	**orig_env;
	char	*cmd_line;
	char	**cmd_parsed;
	char	*prompt;
	char	**copy_env;
}						t_data;

extern t_data	g_data;

// my_execve.c
int		my_execve(char **args);

// my_export
void my_export(char **args);
int is_space(char c);
int	name_is_valid(char **args);

// my_unset
void my_unset(char **args);

// init.c
void	init_vars(char **env);

//builtin_launcher.c
int		look_for_builtin(char **args);
// builtin_echo.c
void	builtin_echo(char **args);
// builtin_cd.c
void	builtin_cd(char **args);
// builtin_pwd.c
int		builtin_pwd(void);

// env_utils.c
char 	*get_env_var(char *var_name, char **env);
int get_env_var_line(char *var_name, char **env);
char	**copy_env_var(char **env);
int	nb_lines_arr(char **array);

// parsing_main.c
char	**parse(char *cmd_line);

// libft_utils_1.c
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *str);
char	*ft_substr(char const *s, unsigned int start, size_t len);

// libft_utils_2.c
char	**ft_split(const char *s, char c);

// libft_utils_3.c
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_bzero(void *s, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_strjoin_with_slash(char const *s1, char const *s2);

// libft_utils_4.c
char *ft_strcpy(char *dest, char *src);
char	*ft_strchr(const char *s, int c);
char	*ft_strldup(const char *s, size_t len);

// free_utils.c
void	free_2d_char(char **arr);

void	exit_minishell(void);

#endif
