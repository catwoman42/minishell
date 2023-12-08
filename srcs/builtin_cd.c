#include "../includes/minishell.h"

// Changer de dossier

// Si aucun argument, répertoire home.
// Si deux arguments ou plus, error.

// Si l'argument est "--", elle change le répertoire vers le répertoire home.
// Si l'argument commence par "-" (et n'a pas plus de deux caractères), elle change le répertoire vers l'ancien répertoire de travail.
// Sinon, elle change le répertoire vers le chemin spécifié.

void builtin_cd(char **args, t_data *datas)
{
	if (args[1] == NULL)
	{
		if (get_env_var("HOME", datas->copy_env) != 0)
		{
			if (chdir(get_env_var("HOME", datas->copy_env)) != 0)
				perror("Erreur lors changement répertoire home");
		}
		else
		{
			fprintf(stderr, "no HOME\n");
		}
	}
	else if (args[2] != NULL)
		fprintf(stderr, "cd: too many arguments\n");
	else
	{
		if (access(args[1], F_OK) != -1)
		{
			if (chdir(args[1]) != 0)
				printf("error");
		}
		else
		{
			printf("cd: %s: No such file or directory\n", args[1]);
		}
	}
}