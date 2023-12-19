/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatoudiallo <fatoudiallo@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 17:53:23 by fatdiall          #+#    #+#             */
/*   Updated: 2023/12/19 18:25:09 by fatdiall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	builtin_cd(char **args, t_data *datas)
{
	int	err;

	err = 0;
	if (args[1] == NULL)
	{
		if (get_env_var("HOME", datas->copy_env) != 0)
			err = chdir(get_env_var("HOME", datas->copy_env));
		else
			return ;
	}
	else if (args[2] != NULL)
		fprintf(stderr, "cd: too many arguments\n");
	else
		err = chdir(args[1]);
	if (err)
	{
		printf("cd: %s: No such file or directory\n", args[1]);
		datas->exit_status = 1;
	}
	else
	{
		free(datas->pwd);
		datas->pwd = getcwd(0, 0);
		datas->exit_status = 0;
	}
}
