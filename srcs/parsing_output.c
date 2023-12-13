#include "../includes/minishell.h"

void	init_out_arr(char **args, t_data *datas)
{
	int	i;
	int	nb_cmds;

	i = -1;
	nb_cmds = 1;
	while (args[++i])
	{
		if (args[i][0] == '|' || args[i][0] == ';')
			nb_cmds++;
	}
	datas->args_arr = malloc(sizeof(char **) * (nb_cmds * 2 + 1));
	i = -1;
	while (++i <= nb_cmds * 2)
		datas->args_arr[i] = NULL;
}

char	**fill_one_line(char **args, char **arr, t_parse *p)
{
	arr = malloc(sizeof(char *) * (p->end - p->start + 2));
	p->i = -1;
	p->j = -1;
	while (++p->i < p->end - p->start + 1)
	{
		if (args[p->start + p->i][0] == '<' || args[p->start + p->i][0] == '>')
			p->i++;
		else
			arr[++p->j] = ft_strdup(args[p->start + p->i]);
	}
	p->i = -1;
	while (++p->i < p->end - p->start + 1)
	{
		if (args[p->start + p->i][0] == '<' || args[p->start + p->i][0] == '>')
		{
			arr[++p->j] = ft_strdup(args[p->start + p->i]);
			if (args[p->start + p->i + 1])
			{
				arr[++p->j] = ft_strdup(args[p->start + p->i + 1]);
				p->i++;
			}
		}
	}
	arr[p->i] = NULL;
	return (arr);
}

void	fill_arr_lines(char **args, t_data *datas, t_parse *p)
{
	int		i;
	int		line;

	line = 0;
	p->start = 0;
	i = -1;
	while (args[++i])
	{
		if ((args[i][0] == '|' || args[i][0] == ';') && i - p->start > 0)
		{
			p->end = i - 1;
			datas->args_arr[line] = fill_one_line(args,
					datas->args_arr[line], p);
			p->start = i + 1;
			datas->args_arr[++line] = malloc(sizeof(char **) * 2);
			datas->args_arr[line][0] = ft_strdup(args[i]);
			datas->args_arr[line][1] = NULL;
			line++;
		}
	}
	p->end = i - 1;
	datas->args_arr[line] = fill_one_line(args, datas->args_arr[line],
			p);
	datas->args_arr[line + 1] = NULL;
}

void	create_output(char **args, t_data *datas)
{
	t_parse	p;

	init_out_arr(args, datas);
	fill_arr_lines(args, datas, &p);
}
