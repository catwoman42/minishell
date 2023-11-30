#include "../includes/minishell.h"

void	exit_minishell(void)
{
	printf("\nExit\n");
	// FREE ALL MALLOCS

	exit(0);
}

void	handlerctrld(int num)
{
	if (num == EOF)
		{
			printf("ctrl -D reçu");
			make_prompt();
		}
}
