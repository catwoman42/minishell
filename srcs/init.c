#include "../includes/minishell.h"

void	make_prompt(t_data *datas)
{
	if (datas->prompt)
		free(datas->prompt);
	datas->prompt = ft_strdup("Minishell > "); // string en dur à changer
}

void	init_vars(char **env, t_data *datas)
{
	datas->err = 0;
	datas->exit = 0;
	datas->orig_env = env;
	datas->copy_env = copy_env_var(env);
	datas->prompt = NULL;
	make_prompt(datas);
}
