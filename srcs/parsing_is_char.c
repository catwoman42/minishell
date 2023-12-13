#include "../includes/minishell.h"

int	is_split_char(char c)
{
	if (c == '|' || c == ';' || c == '<' || c == '>')
		return (1);
	return (0);
}

int	is_only_quotes(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] != '"' && str[i] != '\'')
			return (0);
	}
	return (1);
}

int	is_only_spaces(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (is_spaces(str[i]) != 1)
			return (0);
	}
	return (1);
}
