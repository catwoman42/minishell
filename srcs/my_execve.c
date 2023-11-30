
#include "../includes/minishell.h"

char	*search_path(char **args)
{
	int		i;
	char *path;
	char **paths_in_array;
	char *path_found;

	i = 0;
	path = get_env_var("PATH", g_data.orig_env);
	if (!path)
		return (NULL);
	paths_in_array = ft_split(path, ':');
	while (paths_in_array[i])
	{
		path_found = ft_strjoin_with_slash(paths_in_array[i], args[0]);
		if (access(path_found, F_OK) == 0)
			return (path_found);
		free(path_found);
		i++;
	}
	return (NULL);
}

int	my_execve(char **args)
{
	pid_t	pid;
	char	*prog_path;

	prog_path = search_path(args);
	if (prog_path)
		printf("Found %s at %s\n\n", args[0], prog_path);
	if (!prog_path)
		return(1);
	pid = fork();
	if (pid == -1)
	{
		printf("error while forking");
		return (1);
	}
	else if (pid == 0)
		execve(prog_path, args, NULL);
	else
	{
		int status;
		wait(&status);
	}
	return (0);
}
