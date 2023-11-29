#include "../includes/minishell.h"

void	make_prompt(void)
{
	if (g_data.prompt)
		free(g_data.prompt);
	g_data.prompt = ft_strdup("Minishell > "); // string en dur à changer
}

void	init_vars(char **env)
{
	g_data.err = 0;
	g_data.exit = 0;
	g_data.orig_env = env;
	g_data.copy_env = copy_env_var(env);
	g_data.prompt = NULL;
	make_prompt();
}
