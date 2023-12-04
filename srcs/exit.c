#include "../includes/minishell.h"

void	exit_minishell(t_data *datas)
{
	printf("\nExit\n");
	// FREE ALL MALLOCS
	if (datas->prompt)
		free(datas->prompt);
	free_2d_char(datas->copy_env);
	exit(0);
}

void handlerctrlc(int num)
{
	(void)num;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
