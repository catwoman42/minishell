#include "../includes/minishell.h"

int	builtin_pwd(void)
{
	char cwd[1024];

	getcwd(cwd, sizeof(cwd));
	printf("Current working dir: %s\n", cwd);
	return (0);
}
