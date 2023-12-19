/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env_vars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatoudiallo <fatoudiallo@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 19:09:42 by fatoudiallo       #+#    #+#             */
/*   Updated: 2023/12/13 19:09:45 by fatoudiallo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*replace_var_in_str(char *str, int pos, char *name, char *val)
{
	char	*ret;
	int		i;
	int		j;
	int		s;

	ret = malloc(sizeof(char) * (ft_strlen(str)
				- ft_strlen(name) + ft_strlen(val) + 2));
	i = -1;
	while (++i < pos)
		ret[i] = str[i];
	s = i;
	j = -1;
	i--;
	while (val[++j])
		ret[++i] = val[j];
	s += ft_strlen(name);
	while (str[++s])
		ret[++i] = str[s];
	ret[i + 1] = '\0';
	return (ret);
}

char	*retrieve_var_from_env(char *var_name, t_data *datas)
{
	char	*val;

	if (var_name[0] == '?')
	{
		if (var_name[1] == '\0')
		{
			val = ft_itoa(datas->exit_status);
			return (val);
		}
	}
	val = get_env_var(var_name, datas->copy_env);
	return (val);
}

char	*check_vars_in_str(char *str, t_data *datas)
{
	char	*start;
	int		end;
	char	*var_name;
	char	*var_val;
	char	*ret;

	start = ft_strchr(str, '$') + 1;
	end = start - str;
	if (is_alpha(str[end]) || str[end] == '_' || str[end++] == '?')
	{
		while (str[end])
		{
			if (is_alpha_num(str[end]) == 0 && str[end] != '_')
				break ;
			end++;
		}
	}
	var_name = ft_strldup(start, end - (int)(start - str));
	var_val = retrieve_var_from_env(var_name, datas);
	if (var_val)
		ret = replace_var_in_str(str, start - str - 1, var_name, var_val);
	else
		ret = replace_var_in_str(str, start - str - 1, var_name, "");
	free(var_name);
	return (ret);
}

char	**replace_vars(char **args, t_data *datas)
{
	int		i;
	char	*tmp;

	i = -1;
	while (args[++i])
	{
		if (args[i][0] != '\'')
		{
			while (ft_strchr(args[i], '$'))
			{
				tmp = check_vars_in_str(args[i], datas);
				free(args[i]);
				args[i] = tmp;
			}
		}
	}
	return (args);
}
