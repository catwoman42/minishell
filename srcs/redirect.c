#include "../includes/minishell.h"

int redirection (char *type_red, char *file_name)
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
	}	return 0;
}

// lit depuis l'input ce qu'il y a entre les delimiteurs
// et l'affiche sur le terminal
// 1er arg = commande
// last arg = delimiter


// void    here_doc(char **args, t_data *datas)
// {
//     int i;

//     i = 0;
//     while (args[i] != NULL)
//     {

//     }
// }
