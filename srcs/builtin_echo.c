/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatdiall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 17:56:09 by fatdiall          #+#    #+#             */
/*   Updated: 2023/12/13 17:56:47 by fatdiall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	builtin_echo(char **args)
{
	int	i;
	int	option_n;

	i = 1;
	option_n = 0;
	while (args[i] != NULL)
	{
		if (args[i][0] == '-' && args[i][1] == 'n')
		{
			i++;
			option_n = 1;
		}
		printf("%s", args[i]);
		if (args[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (!option_n)
		printf("\n");
}
