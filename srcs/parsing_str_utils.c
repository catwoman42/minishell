/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_str_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloussig <rloussig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 17:19:09 by rloussig          #+#    #+#             */
/*   Updated: 2023/12/01 17:19:09 by rloussig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_trim(char *str)
{
	int		start;
	int		end;
	char	*ret;
	int		i;

	start = 0;
	while (str[start] && is_spaces(str[start]))
		start++;
	end = ft_strlen(str) - 1;
	while (end >= 0 && is_spaces(str[end]))
		end--;
	ret = malloc(sizeof(char) * (end - start + 3));
	i = 0;
	while (start <= end)
	{
		ret[i] = str[start];
		start++;
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

char	**trim_all_str(char **args)
{
	int		i;
	char	*tmp;

	i = -1;
	while (args[++i])
	{
		if (is_only_spaces(args[i]) || is_only_quotes(args[i]))
		{
			args = rm_arr_line(args, i);
			i--;
		}
		else
		{
			ft_reduce_multiple_spaces(args[i]);
			tmp = ft_trim(args[i]);
			free(args[i]);
			args[i] = tmp;
		}
	}
	return (args);
}

char	*ft_reduce_multiple_spaces(char *str)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	j = -1;
	flag = 0;
	while (str[++j])
	{
		if (!is_spaces(str[j]))
		{
			str[i++] = str[j];
			flag = 0;
		}
		else
		{
			if (flag == 0)
				str[i++] = ' ';
			else
				j++;
			flag = 1;
		}
	}
	str[i] = '\0';
	return (str);
}
