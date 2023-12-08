#include "../includes/minishell.h"

int redirection (char **args, char *type_red, char **file_name)
{
	int fileDescriptor;
	int     option = 0;
    char    **envp; // Empty environment variables array

	pid_t pid;

	if (ft_strcmp(type_red, ">") == 0)
		option = 0;
	if (ft_strcmp(type_red, "<") == 0)
		option = 1;
	if (ft_strcmp(type_red, ">>") == 0)
		option = 2;
	if ((pid = fork()) == -1)
	{
		printf("Child process could not be created\n");
		return (-1);
	}
	if (pid == 0)
	{
		if (option == 0)
		{
			fileDescriptor = open(file_name[0], O_CREAT | O_TRUNC | O_WRONLY, 0600);
			dup2(fileDescriptor, STDOUT_FILENO);
			close(fileDescriptor);
		}
		else if (option == 1)
		{
			fileDescriptor = open(file_name[0], O_RDONLY, 0600);
			dup2(fileDescriptor, STDIN_FILENO);
			close(fileDescriptor);
		}
		else if (option == 2)
		{
			fileDescriptor = open(file_name[0], O_CREAT | O_WRONLY | O_APPEND, 0600);
			dup2(fileDescriptor, STDOUT_FILENO);
			close(fileDescriptor);
		}
    envp = (char *[]) {NULL};
		if (execve(args[0], args, envp) == -1)
		{
			printf("err");
			kill(getpid(), SIGTERM);
		}
	}
	waitpid(pid, NULL, 0);
	return 0;
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
