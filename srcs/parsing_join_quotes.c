/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_join_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloussig <rloussig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 17:19:14 by rloussig          #+#    #+#             */
/*   Updated: 2023/12/01 17:21:54 by rloussig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*merge_args(char **args, int start, int end, char *tmp)
{
	int		i;
	int		j;

	j = -1;
	while (start <= end)
	{
		i = 0;
		while (args[start][++i + 1])
			tmp[++j] = args[start][i];
		start++;
	}
	tmp[j + 1] = '\0';
	return (tmp);
}

char	**join_quotes(char **args, int start, int end)
{
	int		len;
	int		i;
	char	*tmp;

	i = start;
	len = 0;
	while (i <= end)
	{
		len += (int)ft_strlen(args[i]);
		i++;
	}
	tmp = malloc(sizeof(char) * (1 + len));
	tmp = merge_args(args, start, end, tmp);
	free(args[start]);
	args[start] = tmp;
	i = -1;
	while (++i < end - start)
		rm_arr_line(args, start + 1);
	return (args);
}

char	**check_quotes_to_join(char **args)
{
	int		i;
	int		j;

	i = -1;
	while (args[++i])
	{
		if (args[i][0] == '\'' || args[i][0] == '"')
		{
			j = i;
			while (args[j + 1])
			{
				if (args[j + 1][0] == '\'' || args[j + 1][0] == '"')
					j++;
				else
					break ;
			}
			if (j > i)
			{
				join_quotes(args, i, j);
				i = j;
			}
		}
	}
	return (args);
}
