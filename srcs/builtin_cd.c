#include "../includes/minishell.h"

// Changer de dossier

void builtin_cd(char **args)
{
	if (args[1] == NULL)
	{
		if (chdir(getenv("HOME")) != 0)
			printf("error1\n");
	}
	else if (args[2] != NULL)
		printf("trop d'args");
}
