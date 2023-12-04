#include "../includes/minishell.h"

int	name_is_valid(char **args)
{
	const char *equal;
	int	name_len;

	equal = ft_strchr(args[1], '=');
	name_len = equal - args[1];
	if (name_len < 1)
		return (1);
	if ((args[1][0] >= 'a' && args[1][0] <= 'z')
			|| (args[1][0] >= 'A' && args[1][0] <= 'Z')
				|| args[1][0] == '_')
		return (0);
	else if (args[1][0] >= '0' && args[1][0] <= '9')
		return (1);
	else
		return (1);
}

void my_export(char **args, t_data *datas)
{
	int	name_len;
	int		line;
	const char *equal;
	char	*var_name;
	char 	**temp_env;

	equal = ft_strchr(args[1], '=');
	name_len = equal - args[1];
	var_name = ft_strldup(args[1], name_len);
	line = get_env_var_line(var_name, datas->copy_env);
	if (name_is_valid(args) == 0)
	{
		if (line >= 0)
		{
			free(datas->copy_env[line]);
			datas->copy_env[line] = ft_strdup(args[1]);
		}
		else
		{
			temp_env = copy_env_var(datas->copy_env);
			free_2d_char(datas->copy_env);
			temp_env[nb_lines_arr(temp_env)] = ft_strdup(args[1]);
			datas->copy_env = temp_env;
		}
	}
	else
		printf ("error naming\n");
}
