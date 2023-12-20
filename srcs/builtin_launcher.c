/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_launcher.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelloussignian <raphaelloussignian@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 17:57:05 by fatdiall          #+#    #+#             */
/*   Updated: 2023/12/20 14:46:30 by raphaellous      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Recherche dans les fonctions implémentées

void	prt_env(char **args, int declarex)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (declarex)
			printf("declare -x %s\n", args[i]);
		else
			printf("%s\n", args[i]);
		i++;
	}
}

int builtin_with_pipe(char **args, t_data *datas, int haspipe)
{
	pid_t	pid;
	int		fd[2];

	if (haspipe)
		pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		do_redir_child(fd, haspipe, datas->file_redir_out);
		if (ft_strcmp(args[0], "echo") == 0)
			builtin_echo(args);
		else if (ft_strcmp(args[0], "pwd") == 0)
			builtin_pwd(datas);
		exit_minishell(datas);
	}
	do_redir_parent(fd, haspipe);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, 0, 0);
	signal(SIGINT, handlerctrlc);
	datas->exit_status = 0;
	return (0);
}

int	look_for_builtin(char **args, t_data *datas, int haspipe)
{
	if (ft_strcmp(args[0], "echo") == 0 ||
		ft_strcmp(args[0], "pwd") == 0)
		builtin_with_pipe(args, datas, haspipe);
	else if (ft_strcmp(args[0], "cd") == 0)
		builtin_cd(args, datas);
	else if (ft_strcmp(args[0], "exit") == 0)
		exit_minishell(datas);
	else if (ft_strcmp(args[0], "env") == 0)
		prt_env(datas->copy_env, 0);
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
