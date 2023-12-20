/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelloussignian <raphaelloussignian@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 18:06:30 by fatdiall          #+#    #+#             */
/*   Updated: 2023/12/20 14:21:25 by raphaellous      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sub_unset(char **args, t_data *datas, int i)
{
	char		*var_name;
	char		**temp_env;
	int			name_len;
	int			line;

	line = 0;
	name_len = ft_strlen(args[i]);
	var_name = ft_strldup(args[i], name_len);
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
	free(var_name);
	temp_env = copy_env_var(datas->copy_env);
	free_2d_char(datas->copy_env);
	datas->copy_env = temp_env;
}

void	my_unset(char **args, t_data *datas)
{
	int	i;

	i = 1;
	while (args[i])
	{
		sub_unset(args, datas, i);
		++i;
	}
}
