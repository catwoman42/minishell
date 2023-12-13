#include "../includes/minishell.h"

//lire jusqu a \n

char	*read_until_bsn(int fd, char *remain_buffer)
{
	char	*buf;
	char	*temp;
	int		bytes_read;

	bytes_read = 1;
	if (!remain_buffer)
		remain_buffer = ft_calloc(1, sizeof(char));
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	while (bytes_read && ft_strchr(remain_buffer, '\n') == NULL)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		buf[bytes_read] = '\0';
		temp = remain_buffer;
		remain_buffer = ft_strjoin(remain_buffer, buf);
		free(temp);
	}
	free(buf);
	return (remain_buffer);
}
//recuperer la ligne lue jusqu au \n
//et l envoyer au return de gnl

char	*line_read(char *buffer)
{
	char	*the_whole_line;
	int		i;

	if (buffer[0] == '\0')
		return (NULL);
	i = 0 ;
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	the_whole_line = ft_calloc(i + 2, sizeof(char));
	i = 0 ;
	while (buffer[i] != '\n' && buffer[i] != '\0')
	{
		the_whole_line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		the_whole_line[i] = '\n';
	return (the_whole_line);
}

//stocker le reste dans le buffer
char	*after_bsn(char *remain_buffer)
{
	char	*remain_char;
	int		i;
	int		j;
	int		remain_bytes;

	i = 0;
	if (!remain_buffer[i])
	{
		free(remain_buffer);
		return (NULL);
	}
	while (remain_buffer[i] != '\n' && remain_buffer[i] != '\0')
		i++;
	remain_bytes = ft_strlen(remain_buffer) - i;
	remain_char = ft_calloc(remain_bytes + 3, sizeof(char));
	j = 0;
	if (remain_buffer[0])
	{
		i += 1;
		while (j < remain_bytes)
			remain_char[j++] = remain_buffer[i++];
	}
	free(remain_buffer);
	return (remain_char);
}

char	*get_next_line(int fd)
{
	static char	*remain_buffer;
	char		*line;

	if (fd < 0 || read(fd, 0, 0) < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	remain_buffer = read_until_bsn(fd, remain_buffer);
	line = line_read(remain_buffer);
	remain_buffer = after_bsn(remain_buffer);
	return (line);
}

/*int	main(void)
{
	char	*line;
	int		fd;
	int		i;

	fd = open("test.txt", O_RDONLY);
	i = 0;
	while (i < 30)
	{
		line = get_next_line(fd);
		printf("[%d]%s$", i, line);
		free(line);
		i++;
	}
	return (0);
}*/
