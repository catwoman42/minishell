#include "../includes/minishell.h"

char	**parse(char *cmd_line)
{
	char	**args;

	args = ft_split(cmd_line, ' ');

	return (args);
}
