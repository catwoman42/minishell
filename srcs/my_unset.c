#include "../includes/minishell.h"

void	my_unset(char **args, t_data *datas)
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
	line = get_env_var_line(var_name, datas->copy_env);
	if (line >= 0)
	{
		free(datas->copy_env[line]);
		while (datas->copy_env[line] != NULL)
		{
			datas->copy_env[line] = datas->copy_env[line + 1];
			++line;
		}
	}
	temp_env = copy_env_var(datas->copy_env);
	free_2d_char(datas->copy_env);
	datas->copy_env = temp_env;
}
