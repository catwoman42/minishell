/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_splits.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloussig <rloussig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 17:22:04 by rloussig          #+#    #+#             */
/*   Updated: 2023/12/01 17:22:10 by rloussig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**split_cmds_exec(char **args, int i, int j)
{
	char	**tmp;

	tmp = add_str_arr_pos(args, i + 1, ft_strdup(args[i] + j));
	free(args);
	args = tmp;
	tmp = add_str_arr_pos(args, i + 2, ft_strdup(args[i] + j + 1));
	free(args);
	args = tmp;
	args[i][j] = '\0';
	args[i + 1][1] = '\0';
	return (args);
}

char	**split_cmds(char **args)
{
	int		i;
	int		j;

	i = -1;
	while (args[++i])
	{
		if (args[i][0] == '\'' || args[i][0] == '"')
			continue ;
		j = -1;
		while (args[i][++j])
		{
			if (is_split_char(args[i][j]))
			{
				if (args[i][j + 1] == args[i][j])
					j++;
				args = split_cmds_exec(args, i, j);
				i++;
				break ;
			}
		}
	}
	return (args);
}

char	**split_spaces(char **args)
{
	int		i;
	int		j;
	char	**tmp;

	i = -1;
	while (args[++i])
	{
		j = -1;
		if (args[i][0] == '\'' || args[i][0] == '"')
			continue ;
		while (args[i][++j])
		{
			if (is_spaces(args[i][j]))
			{
				tmp = add_str_arr_pos(args, i + 1, ft_strdup(args[i] + j + 1));
				free(args);
				args = tmp;
				args[i][j] = '\0';
				break ;
			}
		}
	}
	return (args);
}
