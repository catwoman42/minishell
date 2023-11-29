#include "../includes/minishell.h"

// Récupère la valeur d'une variable d'env.

char *get_env_var(char *var_name, char **env)
{
	int	i;
	int	name_len;

	i = 0;
	name_len = ft_strlen(var_name);
	while (env[i])
	{
		if (ft_strncmp(var_name, env[i], name_len) == 0)
		{
			if (env[i][name_len] == '=')
				return (env[i] + name_len + 1);
		}
			i++;
	}
	return (NULL);
}

int get_env_var_line(char *var_name, char **env)
{
	int	i;
	int	name_len;

	i = 0;
	name_len = ft_strlen(var_name);
	while (env[i])
	{
		if (ft_strncmp(var_name, env[i], name_len) == 0)
		{
			if (env[i][name_len] == '=')
				return (i);
		}
			i++;
	}
	return (-1);
}

char	**copy_env_var(char **env)
{
	int	len_env;
	char **copy;
	int	i;

	len_env = 0;
	i = 0;
	while (env[len_env] != NULL)
		len_env++;
	copy = malloc(sizeof(char *) * (len_env + 2));
	if (copy  == NULL)
	{
		printf("error copy_env");
		exit (EXIT_FAILURE);
	}
	while (i < len_env)
	{
		copy[i] = malloc(ft_strlen(env[i]) + 1);
		if (env[i] == NULL)
			{
				printf("error lignes");
				exit (EXIT_FAILURE);
			}
			ft_strcpy(copy[i], env[i]);
			i++;
	}
	copy[len_env] = NULL;
	copy[len_env + 1] = NULL;
	return (copy);
	// return (g_data.copy_env);
}

int	nb_lines_arr(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return(-1);
	while (array[i])
	{
		i++;
	}
	return (i);
}
