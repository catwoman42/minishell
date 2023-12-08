#include "../includes/minishell.h"

void	make_prompt(t_data *datas)
{
	char	*str;
	char	*str2;
	char	buf[1024];
	int		i;

	if (datas->prompt)
		free(datas->prompt);
	getcwd(buf, 1024);
	i = ft_strlen(buf);
	while (buf[i] != '/')
		i--;
	str = ft_strjoin(RED"Minishell:"YELLOW, buf + i);
	str2 = ft_strjoin(str, RED"$ "NC);
	free(str);
	datas->prompt = str2;
}

void	init_vars(char **env, t_data *datas)
{
	datas->err = 0;
	datas->exit = 0;
	datas->cmd_ret = 0;
	datas->exit_status = 0;
	datas->orig_env = env;
	datas->copy_env = copy_env_var(env);
	datas->prompt = NULL;
	make_prompt(datas);
}
