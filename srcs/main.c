#include "../includes/minishell.h"

void	prt_args(t_data *datas)
{
	int	i = -1;
	while (datas->args_arr[++i])
	{
		printf("\nargs_arr[%d]\n >> ", i);
		int j = -1;
		while (datas->args_arr[i][++j])
			printf("[%d]{%s} ", j, datas->args_arr[i][j]);
		printf("[%d]NULL ", j);
	}
	printf("\nargs_arr[%d] >> NULL", i);
	printf("\n");
}


int	check_redir(char **cmd_line, t_data *datas)
{
	int	i;

	i = 0;
	while (cmd_line[i] != NULL)
	{
		if (ft_strcmp(cmd_line[i], "<") == 0 || ft_strcmp(cmd_line[i], ">>") == 0
			|| ft_strcmp(cmd_line[i], ">") == 0 || ft_strcmp(cmd_line[i], "<<") == 0)
			{
				if (!(cmd_line[i + 1]))
					printf("syntax error near unexpected token `newline'\n");
				else
				{
					redirection(cmd_line[i], cmd_line[i + 1]);
					free(cmd_line[i + 1]);
				}

				free(cmd_line[i]);
				cmd_line[i] = NULL;
			}
			i++;
	}
	return (1);
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
			check_redir(datas->args_arr[i], datas);
			err = look_for_builtin(datas->args_arr[i], datas);	// builtins
			if (err != 0)
				err = my_execve(datas->args_arr[i], datas);		// system program
			if (err)
				printf("%s: command not found\n", datas->args_arr[i][0]);
			dup2(datas->saved_fd_out, STDOUT_FILENO);
			dup2(datas->saved_fd_in, STDIN_FILENO);
		}
			// if (is_redirect(datas->args_arr[i][0][0]) == 0)
		// 	redirection(datas->args_arr[i][0][0], );
	}
	return (err);
}

//char ***args_arr[0] = {"echo", "La maison", NULL};
//char ***args_arr[1] = {"|", NULL};
//char ***args_arr[2] = {"echo", "Coucou", NULL};
//char ***args_arr[3] = {"|", NULL};
//char ***args_arr[4] = {"echo", "hello", ">", "file", <, file2, NULL};
//char ***args_arr[4] = NULL

void	main_command_loop(t_data *datas)
{
	int		err;

	(void)err;
	while (!datas->exit)
	{
		err = 0;
		make_prompt(datas);
		datas->cmd_line = readline(datas->prompt);	// lecture ligne de commande

		if (datas->cmd_line == NULL)				// gestion CTRL D > STOP LOOP
			break ;
		if (datas->cmd_line[0])						// si la ligne n'est pas vide
		{
			add_history(datas->cmd_line);			// ajoute la ligne a l'historique

			err = parse(datas->cmd_line, datas);	// parsing (err si les quotes ne ferment pas)
			if (!err)
			{
				prt_args(datas);
				err = cmd_launcher(datas);			// lance les commandes
				clear_data_args_arr(datas);			// free ***data.args_arr
			}
		}
		free(datas->cmd_line);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data	datas;

	(void)argc;
	(void)argv;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handlerctrlc);

	init_vars(env, &datas);

	main_command_loop(&datas);
	// parse("echo asdfa dF\"ads f\"sadf sdf's df's\"0\"\"1\" \"2\"dfg'gdsfgdf'g\" ' dfg'   dfgdfg\"\"yui\"'ohb'ghjk'o'     d\"\"\"gdf \"'g'h|", &datas);
	// prt_args(&datas);
	// clear_data_args_arr(&datas);

	exit_minishell(&datas);

	return (0);
}

/*

// Fonction de gestionnaire de signal pour SIGINT (Ctrl-C)
void sigint_handler(int signo) {
    printf("\nVous avez appuyé sur Ctrl-C. Affichage du prompt : ");
    fflush(stdout);  // Assure que le message est affiché immédiatement

    // logique de traitement ou votre prompt personnalisé

    // Réinitialise le gestionnaire de signal pour SIGINT
    signal(SIGINT, sigint_handler);
}

int main()
{
    // ...
    signal(SIGINT, sigint_handler);
    return 0;
}

*/
