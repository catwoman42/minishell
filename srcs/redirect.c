#include "../includes/minishell.h"

// lit depuis l'entrée terminal ce qu'il y a entre les delimiteurs
// stocke ligne par ligne ce qui est lu dans un fichier temporaire
// lit depuis ce fichier temporaire
// affiche le contenu du fichier sur le terminal

// #define BUFFER_SIZE 1024
// get_next_line(STDIN_FILENO);

void here_doc(char *delimiters, t_data *datas)
{
	char *line;
	int fd_temp = open("temp_file.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);

	datas->here_doc_exists = 1;
	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		//printf("%s", line);
		if (ft_strncmp(line, delimiters, ft_strlen(line) - 1) == 0)
		{
			printf("end\n");
			free(line);
			break;
		}
		write(fd_temp, line, ft_strlen(line));
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	close(fd_temp);
	redirection("<", "temp_file.txt", datas);
}

int redirection(char *type_red, char *file_name, t_data *datas)
{
	int file_descriptor;

	//printf("type_red = %s et file_name = %s \n", type_red, file_name);
	if (ft_strcmp(type_red, ">") == 0)
	{
		file_descriptor = open(file_name, O_CREAT | O_TRUNC | O_WRONLY, 0600);
		if (file_descriptor == -1)
		{
			printf("error creating file");
			return (1);
		}
		dup2(file_descriptor, STDOUT_FILENO);
		close(file_descriptor);
	}
	else if (ft_strcmp(type_red, "<") == 0)
	{
		file_descriptor = open(file_name, O_RDONLY, 0600);
		if (file_descriptor == -1)
		{
			printf("error opening file");
			return (1);
		}
		dup2(file_descriptor, STDIN_FILENO);
		// printf("DUP2: %d\n");
		close(file_descriptor);
	}
	else if (ft_strcmp(type_red, ">>") == 0)
	{
		file_descriptor = open(file_name, O_CREAT | O_WRONLY | O_APPEND, 0600);
		dup2(file_descriptor, STDOUT_FILENO);
		close(file_descriptor);
	}
	else if (ft_strcmp(type_red, "<<") == 0)
		here_doc(file_name, datas);
	return (0);
}
