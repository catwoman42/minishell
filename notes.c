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
