/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatoudiallo <fatoudiallo@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 17:19:19 by rloussig          #+#    #+#             */
/*   Updated: 2023/12/01 17:36:13 by fatoudiallo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	prt_arg(char **args)
{
	int	i;

	i = 0;
	printf("args: ");
	while (args[i])
	{
		printf("%d[%s] ", i, args[i]);
		i++;
	}
	printf("\n\n");
}

char	**join_double_redirs(char **args)
{
	int		i;
	char	*tmp;

	i = -1;
	while (args[++i + 1])
	{
		if ((args[i][0] == '>' || args[i][0] == '<') &&
			args[i][0] == args[i + 1][0])
		{
			tmp = malloc(sizeof(char) * 3);
			tmp[0] = args[i][0];
			tmp[1] = args[i][0];
			tmp[2] = '\0';
			free(args[i]);
			rm_arr_line(args, i + 1);
			args[i] = tmp;
		}
	}
	return (args);
}

char	**parse(char *cmd_line, t_data *datas)
{
	char	**args;
	int		i;

	if (check_quotes_closing(cmd_line) < 0)
		return (NULL);
	args = malloc(sizeof(char *) * 1);
	args[0] = NULL;
	args = analyse_quotes(args, cmd_line);
	// prt_arg(args);
	args = replace_vars(args, datas);
	// prt_arg(args);
	args = split_cmds(args);
	// prt_arg(args);
	args = trim_all_str(args);
	// prt_arg(args);
	args = split_spaces(args);
	// prt_arg(args);
	args = join_double_redirs(args);
	// prt_arg(args);
	args = check_quotes_to_join(args);
	// prt_arg(args);
	create_output(args, datas);
	remove_quotes(datas);
	i = -1;
	while (args[++i])
		free(args[i]);
	free(args);
	return (args);
}

void	clear_data_args_arr(t_data *datas)
{
	int	i;
	int	j;

	i = -1;
	while (datas->args_arr[++i])
	{
		j = -1;
		while (datas->args_arr[i][++j])
			free(datas->args_arr[i][j]);
		free(datas->args_arr[i]);
	}
	free(datas->args_arr);
}
