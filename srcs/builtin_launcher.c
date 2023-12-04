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

int	look_for_builtin(char **args, t_data *datas)
{
	if (ft_strcmp(args[0], "echo") == 0)
		builtin_echo(args);
	else if (ft_strcmp(args[0], "cd") == 0)
	 	builtin_cd(args);
	else if (ft_strcmp(args[0], "pwd") == 0)
		builtin_pwd();
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
