/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatoudiallo <fatoudiallo@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 18:25:17 by fatdiall          #+#    #+#             */
/*   Updated: 2023/12/19 17:34:27 by fatdiall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	make_prompt(t_data *datas)
{
	char	*str;
	char	*str2;
	int		i;

	if (datas->prompt)
		free(datas->prompt);
	i = ft_strlen(datas->pwd);
	while (datas->pwd[i] != '/')
		i--;
	str = ft_strjoin(RED"Minishell:"YELLOW, datas->pwd + i);
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
	datas->redirection_file = NULL;
	datas->type_redir = NULL;
	datas->saved_fd_in = dup(STDIN_FILENO);
	datas->saved_fd_out = dup(STDOUT_FILENO);
	datas->here_doc_exists = 0;
	datas->file_redir_in = 0;
	datas->file_redir_out = 0;
	datas->pwd = getcwd(0, 0);
	make_prompt(datas);
}
