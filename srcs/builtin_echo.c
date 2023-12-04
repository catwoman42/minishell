#include "../includes/minishell.h"

// Imprime l'input

void	builtin_echo(char **args)
{
	int i;
	i = 1;
	while (args[i] != NULL)
	{
		printf("%s", args[i]);
		if (args[i + 1] != NULL)
			printf(" ");
		i++;
	}
	printf("\n");
}
