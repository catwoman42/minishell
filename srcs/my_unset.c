/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatdiall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 18:06:30 by fatdiall          #+#    #+#             */
/*   Updated: 2023/12/19 18:12:51 by fatdiall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	my_unset(char **args, t_data *datas)
{
	char		*var_name;
	char		**temp_env;
	const char	*equal;
	int			line;
	int			name_len;

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
