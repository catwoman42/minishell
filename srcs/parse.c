#include "../includes/minishell.h"

// TO DO : move includes, define and prototypes into the header file
// TO DO : add lexer.c in the Makefile
// TO DO : in parsing_main.c file, replace ft_split by tokenise(cmd_line, 0, 0, false)

// Initialization of the tokens table
char **init_tokens_table()
{
    char **args;

    args = malloc(sizeof(char *) * BUF_CMD_LINE);
    if (!args)
        return NULL;

    args[0] = malloc(sizeof(char) * (BUF_CMD_LINE + 1));
    if (!args[0])
    {
        free(args);
        return NULL;
    }

    return (args);
}

// Free of the memory allocated to the tokens table
void free_memory(char **args)
{
    int i;

    i = 0;
    while (args[i])
    {
        free(args[i]);
        i++;
    }
    free(args);
}


// End of the tokenise function to comply with the norm
char    **tokenise_end(char **args, int i, int j)
{
	args[i][j] = '\0';
	args[i + 1] = NULL;

	if (args[0][0] == '\0')
		args[0] = NULL;

	return (args);
}

// Main tokenise function which transform command line into a tokens table
char **tokenise(char *cmd_line, int token_id, int carac_nb, bool is_quote)
{
	char **args;

	args = init_tokens_table();
	while (*cmd_line)
	{
		if (*cmd_line == '\"' || *cmd_line == '\'')
			is_quote = !is_quote;
		else if (*cmd_line == ' ' && !is_quote)
		{
			args[token_id][carac_nb] = '\0';
			carac_nb = 0;
			token_id++;
			args[token_id] = malloc(sizeof(char) * (BUF_CMD_LINE + 1));
		}
		else
				args[token_id][carac_nb++] = *cmd_line;
		cmd_line++;
	}
	tokenise_end(args, token_id, carac_nb);
	return (args);
}
