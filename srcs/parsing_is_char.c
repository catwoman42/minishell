/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_is_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatoudiallo <fatoudiallo@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 19:09:54 by fatoudiallo       #+#    #+#             */
/*   Updated: 2023/12/13 19:09:56 by fatoudiallo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_split_char(char c)
{
	if (c == '|' || c == ';' || c == '<' || c == '>')
		return (1);
	return (0);
}

int	is_only_quotes(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] != '"' && str[i] != '\'')
			return (0);
	}
	return (1);
}

int	is_only_spaces(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (is_spaces(str[i]) != 1)
			return (0);
	}
	return (1);
}
