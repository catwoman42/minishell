#include "../includes/minishell.h"

t_data g_data;

void	prt_args(char **args)
{
	int	i;

	i = 0;
	printf("args: ");
	while (args[i])
	{
		printf("%d[%s] ", i, args[i]);

		i++;
	}
	printf("\n\n");
}


void	main_command_loop(void)
{
	int		err;
	char	**args;

	(void)err;
	while (!g_data.exit)
	{
		err = 0;
		g_data.cmd_line = readline(g_data.prompt);

		if (g_data.cmd_line == NULL)
			break ;
		if (g_data.cmd_line[0])
		{
			add_history(g_data.cmd_line);

			args = parse(g_data.cmd_line);
			prt_args(args);

			err = look_for_builtin(args);	// builtins
			if (err != 0)
				err = my_execve(args);	// system program
		}
		free(g_data.cmd_line);
	}
}

//char *args[] = {"echo", "La maison", NULL};

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;

	// int		found;
	// char	**args;

	init_vars(env);
	// copy_env_var();
	// prt_args(g_data.copy_env);
	main_command_loop();
	printf("start my_export");
	exit_minishell();

	// exit 42 ? (y)19
	return (0);
}
