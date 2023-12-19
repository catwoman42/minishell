/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils_5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatoudiallo <fatoudiallo@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 18:28:43 by fatdiall          #+#    #+#             */
/*   Updated: 2023/12/19 13:09:28 by fatoudiallo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_nb_char(long n)
{
	int	i;

	if (n == 0)
		return (1);
	i = 0;
	if (n < 0)
	{
		n = -n;
		i++;
	}
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	long	ln;
	int		len;
	char	*str;

	ln = (long) n;
	len = ft_nb_char(ln);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	str[len] = '\0';
	if (ln < 0)
		ln = -ln;
	while (--len >= 0)
	{
		str[len] = (ln % 10) + '0';
		ln /= 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
