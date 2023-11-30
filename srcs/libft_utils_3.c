#include "../includes/minishell.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	unsigned const char	*s;
	size_t				i;

	d = dest;
	s = src;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (d);
}

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*str;

	i = 0;
	str = s;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	total_size;
	void	*ptr;

	total_size = nmemb * size;
	ptr = malloc(total_size);
	if (total_size / nmemb != size)
		return (malloc(0));
	if (nmemb == 0 || size == 0)
		return (NULL);
	if (ptr)
	{
		ft_bzero(ptr, total_size);
	}
	return (ptr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	c;
	char	*str;
	size_t	len1;
	size_t	len2;
	size_t	i;

	str = &c;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	str = malloc(sizeof(char) * len1 + len2 + 1);
	if (!str)
		return (0);
	i = 0;
	while (i < len1)
	{
		str[i] = s1[i];
		i++;
	}
	while (i < len2 + len1)
	{
		str[i] = s2[i - len1];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin_with_slash(char const *s1, char const *s2)
{
	char	c;
	char	*str;
	size_t	len1;
	size_t	len2;
	size_t	i;

	str = &c;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	str = malloc(sizeof(char) * len1 + len2 + 2);
	if (!str)
		return (0);
	i = -1;
	while (++i < len1)
		str[i] = s1[i];
	str[i] = '/';
	while (++i < len2 + len1 + 1)
		str[i] = s2[i - len1 - 1];
	str[i] = '\0';
	return (str);
}
