#include "../includes/minishell.h"

void	my_unset(char **args)
{
	int		line;
	int		name_len;
	char	*var_name;
	const char *equal;
	char **temp_env;

	name_len = 0;
	equal = ft_strchr(args[1], '=');
	if (equal == NULL)
		name_len = equal - args[1];
	var_name = ft_strldup(args[1], name_len);
	line = get_env_var_line(var_name, g_data.copy_env);
	if (line >= 0)
	{
		free(g_data.copy_env[line]);
		while (g_data.copy_env[line] != NULL)
		{
			g_data.copy_env[line] = g_data.copy_env[line + 1];
			++line;
		}
	}
	temp_env = copy_env_var(g_data.copy_env);
	free_2d_char(g_data.copy_env);
	g_data.copy_env = temp_env;
}
