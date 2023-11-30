#include "../includes/minishell.h"

// Changer de dossier

void builtin_cd(char **args)
{
    if (chdir(args[1]) != 0)
        printf("chdir() failed");
}
