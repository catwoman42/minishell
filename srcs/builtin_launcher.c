/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_launcher.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatoudiallo <fatoudiallo@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 17:57:05 by fatdiall          #+#    #+#             */
/*   Updated: 2023/12/19 18:04:27 by fatdiall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Recherche dans les fonctions implémentées

void	prt_env(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		printf("%s\n", args[i]);
		i++;
	}
}

int	look_for_builtin(char **args, t_data *datas, int haspipe)
{
	if (ft_strcmp(args[0], "echo") == 0)
	{
		if (haspipe)
		{
			int	fd[2];
			pipe(fd);
			dup2(fd[0], STDIN_FILENO);
			dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
			close(fd[1]);
		}
		builtin_echo(args);
	}
	else if (ft_strcmp(args[0], "cd") == 0)
		builtin_cd(args, datas);
	else if (ft_strcmp(args[0], "pwd") == 0)
		builtin_pwd(datas);
	else if (ft_strcmp(args[0], "exit") == 0)
		exit_minishell(datas);
	else if (ft_strcmp(args[0], "env") == 0)
		prt_env(datas->copy_env);
	else if (ft_strcmp(args[0], "export") == 0)
		my_export(args, datas);
	else if (ft_strcmp(args[0], "unset") == 0)
		my_unset(args, datas);
	else
		return (1);
	return (0);
}

char	*search_path(char **args, t_data *datas)
{
	char	*path;
	char	**paths_in_array;
	char	*path_found;
	int		i;

	i = 0;
	path = get_env_var("PATH", datas->copy_env);
	if (!path)
		return (NULL);
	paths_in_array = ft_split(path, ':');
	while (paths_in_array[i])
	{
		path_found = ft_strjoin_with_slash(paths_in_array[i], args[0]);
		if (access(path_found, F_OK) == 0)
		{
			free_2d_char(paths_in_array);
			return (path_found);
		}
		free(path_found);
		i++;
	}
	free_2d_char(paths_in_array);
	return (NULL);
}
