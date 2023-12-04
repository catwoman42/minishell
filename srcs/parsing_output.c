/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_output.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloussig <rloussig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 17:19:16 by rloussig          #+#    #+#             */
/*   Updated: 2023/12/01 17:24:34 by rloussig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_out_arr(char **args, t_data *datas)
{
	int	i;
	int	nb_cmds;

	i = -1;
	nb_cmds = 1;
	while (args[++i])
	{
		if (args[i][0] == '|' || args[i][0] == ';')
			nb_cmds++;
	}
	datas->args_arr = malloc(sizeof(char **) * (nb_cmds * 2 + 1));
	i = -1;
	while (++i <= nb_cmds * 2)
		datas->args_arr[i] = NULL;
}

char	**fill_one_line(char **args, char **arr, int start, int end)
{
	int	i;
	int	j;

	arr = malloc(sizeof(char *) * (end - start + 2));
	i = -1;
	j = -1;
	while (++i < end - start + 1)
	{
		if (args[start + i][0] == '<' || args[start + i][0] == '>')
			i++;
		else
			arr[++j] = ft_strdup(args[start + i]);
	}
	i = -1;
	while (++i < end - start + 1)
	{
		if (args[start + i][0] == '<' || args[start + i][0] == '>')
		{
			arr[++j] = ft_strdup(args[start + i]);
			if (args[start + i + 1])
			{
				arr[++j] = ft_strdup(args[start + i + 1]);
				i++;
			}
		}
	}
	arr[i] = NULL;
	return (arr);
}

void	fill_arr_lines(char **args, t_data *datas)
{
	int	i;
	int	start;
	int	line;

	line = 0;
	start = 0;
	i = -1;
	while (args[++i])
	{
		if ((args[i][0] == '|' || args[i][0] == ';') && i - start > 0)
		{
			datas->args_arr[line] = fill_one_line(args,
					datas->args_arr[line], start, i - 1);
			start = i + 1;
			datas->args_arr[++line] = malloc(sizeof(char **) * 2);
			datas->args_arr[line][0] = ft_strdup(args[i]);
			datas->args_arr[line][1] = NULL;
			line++;
		}
	}
	datas->args_arr[line] = fill_one_line(args, datas->args_arr[line],
			start, i - 1);
	datas->args_arr[line + 1] = NULL;
}

void	create_output(char **args, t_data *datas)
{
	init_out_arr(args, datas);
	fill_arr_lines(args, datas);
}

	// int	i = -1;
	// printf("\n\n*** New array ***\n");
	// while (datas->args_arr[++i])
	// {
	// 	printf("\nLine %d\n >> ", i);
	// 	int j = -1;
	// 	while (datas->args_arr[i][++j])
	// 		printf("%s ", datas->args_arr[i][j]);
	// }
	// printf("\n");
