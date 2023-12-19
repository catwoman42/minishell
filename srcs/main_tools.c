/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatdiall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 19:45:49 by fatdiall          #+#    #+#             */
/*   Updated: 2023/12/19 20:45:20 by fatdiall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	prt_args(t_data *datas)
{
	int	i;
	int	j;

	i = -1;
	while (datas->args_arr[++i])
	{
		printf("\nargs_arr[%d]\n >> ", i);
		j = -1;
		while (datas->args_arr[i][++j])
			printf("[%d]{%s} ", j, datas->args_arr[i][j]);
		printf("[%d]NULL ", j);
	}
	printf("\nargs_arr[%d] >> NULL", i);
	printf("\n");
}

int	redir_sign(char **cmd_line, int i)
{
	i = 0;
	if (ft_strcmp(cmd_line[i], "<") == 0
		|| ft_strcmp(cmd_line[i], ">>") == 0
		|| ft_strcmp(cmd_line[i], ">") == 0
		|| ft_strcmp(cmd_line[i], "<<") == 0)
		return (0);
	return (1);
}

int	check_redir(char **cmd_line, t_data *datas)
{
	int	i;

	i = 0;
	while (cmd_line[i] != NULL)
	{
		if (redir_sign(cmd_line, i) == 0)
		{
			if (!(cmd_line[i + 1]))
				printf("syntax error near unexpected token `newline'\n");
			if (!(cmd_line[i + 1]))
				return (1);
			else
			{
				redirection(cmd_line[i], cmd_line[i + 1], datas, 0);
				free(cmd_line[i + 1]);
			}
			free(cmd_line[i]);
			cmd_line[i] = NULL;
			i++;
		}
		i++;
	}
	return (0);
}

void	reset_redirs(t_data *datas)
{
	if (datas->file_redir_out)
		dup2(datas->saved_fd_out, STDOUT_FILENO);
	if (datas->here_doc_exists == 1)
		unlink("temp_file.txt");
	datas->here_doc_exists = 0;
	datas->file_redir_out = 0;
	datas->file_redir_in = 0;
}
