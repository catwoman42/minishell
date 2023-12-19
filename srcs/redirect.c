/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatoudiallo <fatoudiallo@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 19:13:31 by fatdiall          #+#    #+#             */
/*   Updated: 2023/12/19 12:27:35 by fatoudiallo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	here_doc(char *delimiters, t_data *datas)
{
	char	*line;
	int		fd_temp;

	fd_temp = open("temp_file.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	datas->here_doc_exists = 1;
	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		if (ft_strncmp(line, delimiters, ft_strlen(line) - 1) == 0)
		{
			// printf("end\n");
			free(line);
			break ;
		}
		write(fd_temp, line, ft_strlen(line));
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	close(fd_temp);
	redirection("<", "temp_file.txt", datas);
}

int	redirection_double(char *type_red, char *file_name, t_data *datas)
{
	int	file_descriptor;

	if (ft_strcmp(type_red, ">>") == 0)
	{
		file_descriptor = open(file_name, O_CREAT | O_WRONLY | O_APPEND, 0600);
		dup2(file_descriptor, STDOUT_FILENO);
		datas->file_redir_out = 1;
		close(file_descriptor);
	}
	else if (ft_strcmp(type_red, "<<") == 0)
		here_doc(file_name, datas);
	return (0);
}

int	redirection(char *type_red, char *file_name, t_data *datas)
{
	int	file_descriptor;

	if (ft_strcmp(type_red, ">") == 0)
	{
		file_descriptor = open(file_name, O_CREAT | O_TRUNC | O_WRONLY, 0600);
		if (file_descriptor == -1)
			printf("error creating file");
		if (file_descriptor == -1)
			return (1);
		dup2(file_descriptor, STDOUT_FILENO);
		datas->file_redir_out = 1;
		close(file_descriptor);
	}
	else if (ft_strcmp(type_red, "<") == 0)
	{
		file_descriptor = open(file_name, O_RDONLY, 0600);
		if (file_descriptor == -1)
			printf("error opening file");
		if (file_descriptor == -1)
			return (1);
		dup2(file_descriptor, STDIN_FILENO);
		datas->file_redir_in = 1;
		close(file_descriptor);
	}
	else
		redirection_double(type_red, file_name, datas);
	return (0);
}
