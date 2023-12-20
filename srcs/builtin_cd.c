/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelloussignian <raphaelloussignian@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 17:53:23 by fatdiall          #+#    #+#             */
/*   Updated: 2023/12/20 14:36:41 by raphaellous      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	update_pwd(t_data *datas)
{
	char	*str;
	char	*str2;

	datas->pwd = getcwd(0, 0);
	str = get_env_var("PWD", datas->copy_env);
	if (str)
	{
		str2 = ft_strjoin("OLDPWD=", str);
		export_helper(datas, str2);
		free(str2);
	}
	str = ft_strjoin("PWD=", datas->pwd);
	export_helper(datas, str);
	free(str);
}

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
		update_pwd(datas);
		datas->exit_status = 0;
	}
}
