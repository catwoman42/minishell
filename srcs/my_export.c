/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelloussignian <raphaelloussignian@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 19:09:57 by fatdiall          #+#    #+#             */
/*   Updated: 2023/12/20 14:15:52 by raphaellous      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	name_is_valid(char **args, int i)
{
	const char	*equal;
	int			name_len;

	equal = ft_strchr(args[i], '=');
	if (equal != NULL)
		name_len = equal - args[i];
	else
		name_len = ft_strlen(args[i]);
	if (name_len < 1)
		return (1);
	if ((args[i][0] >= 'a' && args[i][0] <= 'z')
			|| (args[i][0] >= 'A' && args[i][0] <= 'Z')
				|| args[i][0] == '_')
		return (0);
	else if (args[i][0] >= '0' && args[i][0] <= '9')
		return (1);
	else
		return (1);
}

void sub_export(char **args, t_data *datas, int i, int line)
{
	char		*var_name;
	char		**temp_env;
	int			name_len;

	name_len = (ft_strchr(args[i], '=')) - args[1];
	var_name = ft_strldup(args[i], name_len);
	line = get_env_var_line(var_name, datas->copy_env);
	if (name_is_valid(args, i) == 0)
	{
		if (line >= 0)
			free(datas->copy_env[line]);
		if (line >= 0)
			datas->copy_env[line] = ft_strdup(args[i]);
		else
		{
			temp_env = copy_env_var(datas->copy_env);
			free_2d_char(datas->copy_env);
			temp_env[nb_lines_arr(temp_env)] = ft_strdup(args[i]);
			datas->copy_env = temp_env;
		}
	}
	else
		printf ("error: %s: not a valid identifier\n", var_name);
	if (var_name)
		free(var_name);
}

void	my_export(char **args, t_data *datas)
{
	int			i;

	i = 1;
	while (args[i])
	{
		if (ft_strchr(args[i], '=') != NULL)
			sub_export(args, datas, i, 0);
		++i;
	}
}

void	export_helper(t_data *datas, char *str)
{
	char	**args;

	args = malloc(sizeof(char *) * 3);
	args[0] = ft_strdup("export");
	args[1] = ft_strdup(str);
	args[2] = NULL;
	my_export(args, datas);
	free(args[0]);
	free(args[1]);
	free(args);
}
