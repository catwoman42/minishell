#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <sys/wait.h>
#include<time.h>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "DanglingPointer"
#define MAX_LIMIT 100

char log_path[MAX_LIMIT];
char *variable_table[MAX_LIMIT][2] = {NULL};
int table_place = 0;

//Takes the raw input of the user
//Returns the same string while fixing white spaces and replacing variables from table
char *fix_input(const char *command)
{
	char *fixed_command = malloc((MAX_LIMIT + 1) * sizeof(char));
	int i = 0;		// i -> original command counter
	int j = 0;   // j -> new command counter

	while(command[i] != '\0')
	{
		if(isspace(command[i]) && isspace(command[i+1]))
		{   //skips multiple spaces
				i++;
				continue;
		}
		else if(command[i] == '$')
		{     //replaces variable
			char var_name[MAX_LIMIT];
			//            i++;
			int k = 0;
			int n = i + 1;
			while(!isspace(command[n]) && command[n] != '\"' && command[n] != '\0')
			{  //parses the variable name until a space encountered
					var_name[k++] = command[n++];
			}
			var_name[k] = '\0';
			char *var_value = NULL;
			int l = 0;

			while( l < table_place)
			{   //searches for the variable in variable table
				if(!strcmp(variable_table[l][0], var_name))
				{
						var_value = variable_table[l][1];
						break;
				}
				l++;
			}

			if(var_value != NULL)
			{
				int l = 0;
				while ( l < strlen(var_value))
				{     //adds variable value into fixed command
					fixed_command[j++] = var_value[l];
					l++;
				}
				i = n;
				continue;
			}
		}
		fixed_command[j++] = command[i++];
	}
	fixed_command[j] = '\0';
	return (fixed_command);
}

// Parse the fixed input while searching for & (background process)
// Returns an array of tokens
char ** parse_input(char * command, bool * background)
{
	char ** args = malloc(MAX_LIMIT * sizeof(char*));
	args[0] = malloc((MAX_LIMIT+1) * sizeof(char));
	bool is_quote = false;
	int j = 0, k = 0;   //j -> token number, k -> character number inside the token
	for(int i = 0; i < strlen(command); i++)
	{
		if(command[i] == '\"')
		{     //quoted text is left untouched
			is_quote = !is_quote;   //altering the state between leading and terminating quotations
			continue;
		}
		else if (isspace(command[i]) && !is_quote)
		{     //skips quoted text as it doesn't end when encountering a space
			args[j][k] = '\0';
			k = 0;
			j++;
			args[j] = malloc((MAX_LIMIT+1) * sizeof(char));     //allocating next token
			if(command[i-1] == '&')
					j--;    //to balance the increment when we find the space
			continue;
		}
		else if(command[i] == '&' && !is_quote)
		{   //skipping & while setting the background boolean
			*background = true;
			continue;
		}
		args[j][k++] = command[i];
	}
	args[j][k] = '\0';  //terminating the string
	args[j+1] = NULL;   //appending NULL to last element
	if(args[0][0] == '\0')
			args[0] = NULL;
	return args;
}

//Adds new variable into the variable table
//while checking if it already exists to be replaced.
//Used in export command
void get_var(char command[], char variableName[], char value[])
{
	int	j;
	int k = 0;
	int l = 0;   // k -> counter for var name, l -> counter for var value
	bool beforeEqual = true;
	bool isQuote = false;
	int i = 7;
	while (i < strlen(command))
	{   //i = 7 because we will skip "export"
		if(isspace(command[i]) && isspace(command[i-1]) && !isQuote)    //skipping consecutive white spaces
			continue;
		else if(command[i] == '\"')
		{
			isQuote = !isQuote;
			continue;
		}
		else if (command[i] == '=')
		{
			beforeEqual = false;
			continue;
		}
		if(beforeEqual)         //i -> before equal, so it's the variable name
			variableName[k++] = command[i];
		else                    //i -> after equal so it's the value
			value[l++] = command[i];*
			i++;
	}
	variableName[k] = '\0';     //terminating both strings
	value[l] = '\0';
	j = 0;
	while (j < table_place)
	{                   //checking if the variable name already exists in the table
		if(!strcmp(variable_table[j][0], variableName))
		{    //if exits then replace the value
			free(variable_table[j][1]);
			variable_table[j][1] = malloc((strlen(value) + 1) * sizeof(char));
			strcpy(variable_table[j][1], value);
			return;
		}
		j++;
	}
	variable_table[table_place][0] = malloc((strlen(variableName) + 1) * sizeof(char));     //assigning memory locations
	variable_table[table_place][1] = malloc((strlen(value) + 1) * sizeof(char));            //and copy values to it
	strcpy(variable_table[table_place][0], variableName);
	strcpy(variable_table[table_place][1], value);
	table_place++;
	if(table_place == 100)
	{     //exceeding maximum value so rewrite
			table_place = 0;
	}
}

void execute_command(char ** args, bool background)
{
	pid_t child_pid = fork();               //creating a child process
	if(child_pid == 0)
	{                     //checking if process is a child
		execvp(args[0], args);
		printf("Error\n");          //only is done when execution fails (program doesn't exist)
		exit(0);
	}
	else
	{                                 //parent process
		FILE * file = fopen(log_path, "a");
		time_t t = time(NULL);
		char * time_str = ctime(&t);
		time_str[strlen(time_str)-1] = '\0';
		fprintf(file, "%25s %5d %20s %15s\n", time_str ,child_pid, "Process Started", args[0]);
		fclose(file);
		if(!background)
		{
			int child_status;
			waitpid(child_pid, &child_status, 0);
			if(child_pid > 0)
			{
				file = fopen(log_path, "a");
				t = time(NULL);
				time_str = ctime(&t);
				time_str[strlen(time_str)-1] = '\0';
				fprintf(file, "%25s %5d %20s\n", time_str, child_pid, "Process Terminated");
				fclose(file);
			}
		}
	}
}

bool execute_builtin(char * command, char ** args)
{
	if(!strcmp("cd", args[0]))
	{
		char * path = args[1];
		if(path == NULL)
		{
			printf("cd: Please enter a directory\n");
		}
		else
		{
			if(!strcmp(path, "~"))
			{
					path = getenv("HOME");
			}
			if(chdir(path) == -1)
			{
					printf("cd: %s: No such file or directory\n", path);
			}
		}
		return true;
	}
	else if(!strcmp("export", args[0]))
	{
		char varName[MAX_LIMIT];
		char varValue[MAX_LIMIT];
		get_var(command, varName, varValue);
		setenv(varName, varValue, 1) ;
		return true;
	}
	else if(!strcmp("echo", args[0]))
	{
		system(command);
		return true;
	}
		else if (!strcmp("exit", args[0]))
	{
		exit(0);
	}
	else
	{
		return false;
	}
}

void shell(char * command)
{
	bool background = false;
	char * fixed_command = fix_input(command);
	char ** args = parse_input(fixed_command, &background);
	if(args[0] == NULL) return;             //checking for empty command
	if(!execute_builtin(fixed_command, args))
		execute_command(args, background);
	for(int i = 0; i < MAX_LIMIT; i++)
	{     //freeing allocated memory in the heap
		if(args[i] == NULL)
		{
				free(args[i]);
				break;
		}
		free(args[i]);
	}
	free(args);
	free(fixed_command);
}


void on_child_exit()
{
	int wait_stat;
	pid_t child_pid;
	child_pid = waitpid(-1, &wait_stat, WNOHANG);
	if(child_pid > 0)
	{
		FILE * file = fopen(log_path, "a");
		time_t t = time(NULL);
		char * time_str = ctime(&t);
		time_str[strlen(time_str)-1] = '\0';
		fprintf(file, "%25s %5d %20s\n", time_str, child_pid, "Process Terminated");
		fclose(file);
	}
}

int main()
{
	char command[MAX_LIMIT];
	char user[MAX_LIMIT];
	char current_dir[MAX_LIMIT];

	getcwd(log_path, MAX_LIMIT);
	chdir(log_path);
	strcat(log_path, "/logs.txt");
	FILE * file = fopen(log_path, "w");
	fprintf(file, "%25s %5s %20s %15s\n", "Time", "pid", "Status", "Program");
	fclose(file);
	signal(SIGCHLD, on_child_exit);     //Signal handler for background child
	while(true)
	{
		getlogin_r(user, MAX_LIMIT);
		getcwd(current_dir, MAX_LIMIT);
		printf("%s:%s$ ", user, current_dir);
		fgets(command, MAX_LIMIT, stdin);
		command[strcspn(command, "\n")] = 0;
		shell(command);
    }
}



// export chat gpt suggestion

void splitString(const char *input, char ***before, char ***after)
{
    // Recherche de l'indice du caractère '='
    const char *equalSign = strchr(input, '=');

    // if (equalSign == NULL)
		// {
    //     // Le caractère '=' n'est pas présent dans la chaîne
    //     *before = NULL;
    //     *after = NULL;
    //     return;
    // }

    // Calcul de la taille des parties avant et après '='
		// calcul nombre d'éléments entre les deux termes
    size_t beforeSize = equalSign - input;
    size_t afterSize = strlen(equalSign + 1); // +1 pour exclure le '=' lui-même

    // Allocation de mémoire pour les tableaux et copie des parties avant et après '='
    *before = (char **)malloc((beforeSize + 1) * sizeof(char *));
    *after = (char **)malloc((afterSize + 1) * sizeof(char *));

    if (*before == NULL || *after == NULL) {
        // Gestion de l'échec d'allocation
        fprintf(stderr, "Erreur d'allocation de mémoire.\n");
        exit(EXIT_FAILURE);
    }

    strncpy(**before, input, beforeSize);
    (*before)[beforeSize] = '\0';

    strcpy(**after, equalSign + 1);
}

int main()
{
    char inputString[] = "avant=apres";
    char **before;
    char **after;

    splitString(inputString, &before, &after);

    if (before != NULL && after != NULL)
		{
        printf("Avant le '=' : %s\n", *before);
        printf("Après le '=' : %s\n", *after);

        // Libération de la mémoire allouée
        free(*before);
        free(*after);
    }
		else
		{
        printf("Le caractère '=' n'est pas présent dans la chaîne.\n");
    }

    return 0;
}

// Fonction export

void my_export(char **args)
{
	int name_len;
	const char *equal;
	char *var_name;
	char **temp_env;
	int line;

	// ou est le egal ?
	equal = ft_strchr(args[1], '=');
	// taille du nom
	name_len = equal - args[1];
	// Copy du nom avec ft_strldup
	var_name = ft_strldup(args[1], name_len);
	// A quelle ligne est la variable dans l'environnement ?
	line = get_env_var_line(var_name, g_data.copy_env);
	// Si la variable existe, l'update
	if (line >= 0)
	{
		free(g_data.copy_env[line]);
		g_data.copy_env[line] = ft_strdup(args[1]);
	}
	else
	{
		// Sinon créer une copie de l'env.
		temp_env = copy_env_var(g_data.copy_env);
		free_2d_char(g_data.copy_env);

		// Rajouter la nouvelle var
		temp_env[nb_lines_arr(temp_env)] = ft_strdup(args[1]);
		g_data.copy_env = temp_env;
}
}


// redirecting

//implements redirection
int redirection(char *input, int state){

  char cpy[1000], path[1000], command[1000], filename[1000], **args, *temp;
  int spacecount, i = 0, fd;

  sprintf(cpy, "%s", input);

  temp = strtok(cpy, " ");
  sprintf(path, "%s", temp);

  sprintf(cpy, "%s", input);

  if(state == 1){
    temp = strtok(cpy, "<");
    sprintf(command, "%s", temp);
    command[strlen(command) - 1] = '\0';
    temp[strlen(temp) - 1] = '\0';

    temp = strtok(NULL, "\0");
    sprintf(filename, "%s", temp);
    trim(filename);

    spacecount = whitespaceCount(command, strlen(command));

    args = calloc((spacecount)+2, sizeof(char *));
    for(i = 0; i < spacecount + 1; i ++){
      args[i] = calloc(strlen(command)+10, sizeof(char));
    }

    i = stitch(command, args);

    if((fd = open(filename, O_RDONLY, 0644)) < 0){
      perror("open error");
      return -1;
    }

    dup2(fd, 0);
    close(fd);

    execvp(path, (char *const *)args);
    perror("execvp error");
    _exit(EXIT_FAILURE);

  }else if(state == 2){
    temp = strtok(cpy, ">");
    sprintf(command, "%s", temp);
    command[strlen(command) - 1] = '\0';
    temp[strlen(temp) - 1] = '\0';

    temp = strtok(NULL, "\0");
    sprintf(filename, "%s", temp);
    trim(filename);

    spacecount = whitespaceCount(command, strlen(command));

    args = calloc((spacecount)+2, sizeof(char *));

    for(i = 0; i < spacecount + 1; i ++){
      args[i] = calloc(strlen(command)+10, sizeof(char));
    }

    i = stitch(command, args);

    if((fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644)) < 0){
      perror("open error");
      return -1;
    }

    dup2(fd, 1);
    close(fd);

    execvp(path, (char *const *)args);
    perror("execvp error");
    _exit(EXIT_FAILURE);

  }else if(state == 3){
    char filename2[1000];
    int fd2;

    temp = strtok(cpy, "<");
    sprintf(command, "%s", temp);
    command[strlen(command) - 1] = '\0';
    temp[strlen(temp) - 1] = '\0';

    temp = strtok(NULL, ">");
    sprintf(filename, "%s", temp);
    filename[strlen(filename) - 1] = '\0';
    temp[strlen(temp) - 1] = '\0';
    trim(filename);

    temp = strtok(NULL, "\0");
    sprintf(filename2, "%s", temp);
    trim(filename2);

    spacecount = whitespaceCount(command, strlen(command));

    args = calloc((spacecount)+2, sizeof(char *));
    for(i = 0; i < spacecount + 1; i ++){
      args[i] = calloc(strlen(command)+10, sizeof(char));
    }

    i = stitch(command, args);

    if((fd = open(filename, O_RDONLY, 0644)) < 0){
      perror("open error");
      return -1;
    }

    if((fd2 = open(filename2, O_CREAT | O_WRONLY | O_TRUNC, 0644)) < 0){
      perror("open error");
      return -1;
    }

    dup2(fd, 0);
    close(fd);

    dup2(fd2, 1);
    close(fd2);

    execvp(path, (char *const *)args);
    perror("execvp error");
    _exit(EXIT_FAILURE);

  }
  return 1;
}


// piping

int do_pipe(char **in, int *pipecount, int i)
{
  if(i == *pipecount - 1)
	{
    //last process

    int x, spacecount, c;
    char ** args, cpy[1000];
    sprintf(cpy, "%s", in[i]);

    spacecount = whitespaceCount(in[i], strlen(in[i]));


    args = calloc((spacecount)+2, sizeof(char *));
    for(c = 0; c < spacecount + 1; c++){
      args[c] = calloc(strlen(in[i])+10, sizeof(char));
    }
    stitch(cpy, args);

    if((x = redirectionCheck(in[i])) < 0){
        execvp(args[0], args);
        perror("execvp error");
        _exit(EXIT_FAILURE);
      }
      redirection(in[i], x);
      return 1;
  }
  if(i < *pipecount)
	{
    int fd[2], x, status, spacecount, c;
    pid_t pid;
    char ** args, cpy[1000];

    if(pipe(fd) < 0){
      perror("pipe");
      _exit(EXIT_FAILURE);
    }

    if((pid = fork()) < 0)
		{
      perror("fork");
      _exit(EXIT_FAILURE);
    }

    if(pid != 0){
      dup2(fd[1], 1);
      close(fd[0]);
      in[i+1] = NULL;

      sprintf(cpy, "%s", in[i]);

      spacecount = whitespaceCount(in[i], strlen(in[i]));

      args = calloc((spacecount)+2, sizeof(char *));
      for(c = 0; c < spacecount + 1; c++)
			{
        args[c] = calloc(strlen(in[i])+10, sizeof(char));
      }
      stitch(cpy, args);

      if((x = redirectionCheck(in[i])) < 0)
			{
        execvp(args[0], args);
        perror("execvp error");
        _exit(EXIT_FAILURE);
      }

      redirection(in[i], x);
      waitpid(-1, &status, 0); //wait for all child processes to finish

    }else{
      if(i != *pipecount-1)
			{
        dup2(fd[0], 0);
      }
      close(fd[1]);

      i+=1;
      do_pipe(in, pipecount, i);
    }
  }
  return 1;
}


// int main() {
//   int i, argc = 0, status;
//   char **input;
//   char *prompt = "> ";
//   while (1) {
//   	write(1, prompt, 2);
//     input = getline();
//     argc = 0;
//     if(input[0] == NULL){continue;}

//     for (int i = 0; input[i] != NULL; ++i) {
//       argc++;
//     }

//     if(strcmp(input[0], "cd") == 0){
//     	if(argc == 1){
//     		char *home = getenv("HOME");
//     		if(chdir(home) != 0){
//     			perror("chdir error");
//     		}
//     	}else{
//     		if(chdir(input[1]) != 0){
//     			perror("chdir error");
//     		}
//     	}
//     	continue; //prompt user for next command
//     }

//     if(strcmp(input[0], "exit") == 0){
//       waitpid(-1, &status, 0);
//       break;
//     }

//     if (fork() != 0){
//     	//parent
//     	waitpid(-1, &status, 0); //wait for all child processes to finish
//       continue;
//     }else{
//     	int numPipes = pipecount(input, argc);

//       //allocate array to obtain commands for each process
//       char **commands =  calloc(numPipes +1, sizeof(char*));
//       for(i = 0; i < (numPipes +1); i++){
//         commands[i] = calloc((2*argc + 1), sizeof(char));
//       }
//       parse(input, commands, numPipes, argc);

//       if(numPipes == 0){
//         int x = 0;
//         if((x = redirectionCheck(commands[0])) < 0){
//           execvp(input[0], input);
//           perror("execvp error");
//           _exit(EXIT_FAILURE);
//         }
//         redirection(commands[0], x);
//       }

//       //number of pipes seen exceeds zero
//       for(i = 0; i < (numPipes + 1); i++){
//         trim(commands[i]);
//       }
//       int count = numPipes+1;
//       do_pipe(commands, &count, 0);

//     }
//   }
//   return 0;
// }

https://github.com/pranav93y/myshell/tree/master/lib
