/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_join_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelloussignian <raphaelloussignian@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 17:19:14 by rloussig          #+#    #+#             */
/*   Updated: 2023/12/04 12:15:11 by raphaellous      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*merge_args(char **args, int start, int end, char *tmp)
{
	int		i;
	int		j;
	int		has_quotes;

	j = -1;
	while (start <= end)
	{
		i = -1;
		if (args[start][0] == '\'' || args[start][0] == '"')
			i = 0;
		if (args[start][0] == '\'' || args[start][0] == '"')
			has_quotes = 1;
		else
			has_quotes = 0;
		while (args[start][++i + has_quotes])
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

char	**check_elements_to_join(char **args)
{
	int	i;
	int	j;

	i = -1;
	while (args[++i + 1])
	{
		if ((args[i][0] != '\0') && (args[i][0] == '"' || args[i][0] == '\''
			|| args[i + 1][0] == '"' || args[i + 1][0] == '\''))
		{
			j = i;
			while (args[j + 1][0] == '"' || args[j + 1][0] == '\'')
				j++;
			if (args[j + 1])
			{
				if (args[j + 1][0] != '\0')
					j++;
			}
			if (i != j)
				join_quotes(args, i--, j);
		}
	}
	return (args);
}

char	**rm_empty_elements(char **args)
{
	int	i;

	i = -1;
	while (args[++i])
	{
		if (args[i][0] == '\0')
			rm_arr_line(args, i);
	}
	return (args);
}
