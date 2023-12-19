/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatoudiallo <fatoudiallo@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 19:10:15 by fatoudiallo       #+#    #+#             */
/*   Updated: 2023/12/13 19:10:16 by fatoudiallo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	remove_quotes(t_data *datas)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	while (datas->args_arr[++i])
	{
		j = -1;
		while (datas->args_arr[i][++j])
		{
			if (datas->args_arr[i][j][0] == '"'
				|| datas->args_arr[i][j][0] == '\'')
			{
				tmp = ft_strldup(datas->args_arr[i][j] + 1,
						ft_strlen(datas->args_arr[i][j]) - 2);
				free(datas->args_arr[i][j]);
				datas->args_arr[i][j] = tmp;
			}
		}
	}
}

int	get_end_quote(char *str, int start, char type)
{
	while (str[++start])
	{
		if (str[start] == type)
			return (start);
	}
	return (-1);
}

int	check_quotes_closing(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\"')
		{
			i = get_end_quote(str, i, '"');
			if (i < 0)
			{
				printf("Error: Double quote missing\n");
				return (-1);
			}
		}
		else if (str[i] == '\'')
		{
			i = get_end_quote(str, i, '\'');
			if (i < 0)
			{
				printf("Error: Simple quote missing\n");
				return (-1);
			}
		}
	}
	return (0);
}

void	update_counters(int *i, int *endqu)
{
	*i = *endqu;
	*endqu = *endqu + 1;
}

char	**analyse_quotes(char **args, char *str)
{
	int	i;
	int	endqu;

	i = -1;
	endqu = 0;
	while (str[++i])
	{
		if (str[i] == '\"')
		{
			args = add_str_part_to_arr(args, str, endqu, i - 1);
			endqu = get_end_quote(str, i, '\"');
			args = add_str_part_to_arr(args, str, i, endqu);
		}
		else if (str[i] == '\'')
		{
			args = add_str_part_to_arr(args, str, endqu, i - 1);
			endqu = get_end_quote(str, i, '\'');
			args = add_str_part_to_arr(args, str, i, endqu);
		}
		if (str[i] == '\'' || str[i] == '\"')
			update_counters(&i, &endqu);
	}
	args = add_str_part_to_arr(args, str, endqu, i);
	return (args);
}
