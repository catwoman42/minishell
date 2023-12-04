#include "../includes/minishell.h"

void	exit_minishell(void)
{
	printf("\nExit\n");
	// FREE ALL MALLOCS

	exit(0);
}

void	handlerctrld(int num)
{
	// struct sigaction sa;

	// if (num == EOF)
	// 	{
			printf("ctrl -D reçu");
			exit_minishell();
			// sigaction(num, handlerctrld);
		// }
	// sa.sa_handler = handlerctrld;
	// sigaction(SIGINT, &sa, NULL);
}

void handlerctrlc(int num)
{
	printf("ctrl -C reçu");
	// struct sigaction sa;
	// sa.sa_handler = handlerctrlc;
	// sigaction(SIGINT, &sa, NULL);
}
