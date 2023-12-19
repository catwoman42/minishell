/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_arrays_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatoudiallo <fatoudiallo@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 19:09:27 by fatoudiallo       #+#    #+#             */
/*   Updated: 2023/12/13 19:09:30 by fatoudiallo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**add_str_arr_pos(char **arr, int pos, char *str)
{
	int		i;
	int		len;
	char	**ret;

	len = 0;
	while (arr[len])
		len++;
	ret = malloc(sizeof(char *) * (len + 2));
	i = -1;
	if (pos > len)
		pos = len;
	while (++i < pos)
		ret[i] = arr[i];
	ret[i] = str;
	while (++i <= len)
		ret[i] = arr[i - 1];
	ret[i] = NULL;
	return (ret);
}

char	**add_str_part_to_arr(char **args, char *str, int start, int end)
{
	char	*extract;
	char	**ret;

	if (end > (int)ft_strlen(str))
		end = ft_strlen(str);
	if (start > end)
		return (args);
	extract = ft_strldup(str + start, end - start + 1);
	ret = add_str_arr_pos(args, 9999999, extract);
	free(args);
	return (ret);
}

char	**rm_arr_line(char **args, int pos)
{
	free(args[pos]);
	while (args[pos + 1])
	{
		args[pos] = args[pos + 1];
		pos++;
	}
	args[pos] = NULL;
	return (args);
}
