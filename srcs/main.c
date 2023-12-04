#include "../includes/minishell.h"

// t_data g_data;

void	prt_args(t_data *datas)
{
	int	i = -1;
	printf("*** New array ***");
	while (datas->args_arr[++i])
	{
		printf("\nLine %d\n >> ", i);
		int j = -1;
		while (datas->args_arr[i][++j])
			printf("%s ", datas->args_arr[i][j]);
	}
	printf("\n");
}

int	cmd_launcher(t_data *datas)
{
	int	i;
	int		err;

	i = -1;
	while (datas->args_arr[++i])
	{
		if (datas->args_arr[i][0][0] != '|')
		{
			printf("\n>>> Command output:\n");
			err = my_execve(datas->args_arr[i], datas);	// system program
			if (err != 0)
				err = look_for_builtin(datas->args_arr[i], datas);	// builtins
		}
	}
	return (err);
}

void	main_command_loop(t_data *datas)
{
	int		err;

	(void)err;
	while (!datas->exit)
	{
		err = 0;
		datas->cmd_line = readline(datas->prompt);

		if (datas->cmd_line == NULL)
			break ;
		if (datas->cmd_line[0])
		{
			add_history(datas->cmd_line);

			parse(datas->cmd_line, datas);
			prt_args(datas);

			// err = my_execve(args);	// system program
			// if (err != 0)
			// 	err = look_for_builtin(args);	// builtins
			err = cmd_launcher(datas);
			clear_data_args_arr(datas);
		}
		free(datas->cmd_line);
	}
}

//char *args[] = {"echo", "La maison", NULL};

int	main(int argc, char **argv, char **env)
{
	struct sigaction	sa;
	t_data datas;

	(void)argc;
	(void)argv;

	// sa.sa_sigaction = &handlerctrld;
	// sa.sa_handler = handlerctrlclear

  sigaction(SIGQUIT, &sa, NULL);

	sa.sa_handler = handlerctrlc;
  sigaction(SIGINT, &sa, NULL);

	// int		found;
	// char	**args;

	init_vars(env, &datas);
	// copy_env_var();

	main_command_loop(&datas);
	 printf("start my_export");
	exit_minishell();

	if (signal(EOF, handlerctrld) == SIG_ERR)
	{
		printf("error lors config");
		return (1);
	}
	// exit 42 ? (y)19
	while (1)
		usleep(1000);
	return (0);
}

/*

// Fonction de gestionnaire de signal pour SIGINT (Ctrl-C)
void sigint_handler(int signo) {
    printf("\nVous avez appuyé sur Ctrl-C. Affichage du prompt : ");
    fflush(stdout);  // Assure que le message est affiché immédiatement

    // Ajoutez ici votre logique de traitement ou votre prompt personnalisé

    // Réinitialise le gestionnaire de signal pour SIGINT
    signal(SIGINT, sigint_handler);
}

int main()
{
    // Définit le gestionnaire de signal pour SIGINT
    signal(SIGINT, sigint_handler);

    // Votre programme principal ici
    while (1) {
        // Effectuez vos opérations principales ici
    }

    return 0;
}

*/
