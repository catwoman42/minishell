#include "../includes/minishell.h"

// Imprime l'input

void	builtin_echo(char **args)
{
	printf("%s\n", args[1]);
}
