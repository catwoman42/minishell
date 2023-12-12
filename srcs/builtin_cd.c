#include "../includes/minishell.h"

// Changer de dossier

// Si aucun argument, répertoire home.
// Si deux arguments ou plus, error.

// Si l'argument est "--", elle change le répertoire vers le répertoire home.
// Si l'argument commence par "-" (et n'a pas plus de deux caractères), elle change le répertoire vers l'ancien répertoire de travail.
// Sinon, elle change le répertoire vers le chemin spécifié.

void builtin_cd(char **args, t_data *datas)
{
	int err;

	err = 0;
	if (args[1] == NULL)
	{
		if (get_env_var("HOME", datas->copy_env) != 0)
			err = chdir(get_env_var("HOME", datas->copy_env));
		else
			return ;
	}
	else if (args[2] != NULL)
		fprintf(stderr, "cd: too many arguments\n");
	else
		err = chdir(args[1]);
	if (err)
	{
		printf("cd: %s: No such file or directory\n", args[1]);
		datas->exit_status = 1;
	}
	else
		datas->exit_status = 0;
}
