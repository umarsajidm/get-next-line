// #include "get_next_line.h"
#include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>


# ifndef BUFFER_SIZE
# define BUFFER_SIZE 3
# endif

size_t	ft_strlen(const char *c)
{
	int	i;

	i = 0;
	if (!c)
		return (0);
	if (c[i] != '\0')
	{
		while (c[i] != '\0')
			++i;
		return (i);
	}
	else
		return (0);
}

char	*ft_strdup(const char *s)
{
	size_t	i;
	char	*s_dup;

	s_dup = (char *)malloc(ft_strlen(s) + 1);
	i = 0;
	if (!s_dup)
		return (NULL);
	while (s[i] != '\0')
	{
		s_dup[i] = s[i];
		i++;
	}
	s_dup[i] = '\0';
	return (s_dup);
}
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len >= ft_strlen(s + start))
		len = ft_strlen(s + start);
	sub = (char *)malloc(len + 1);
	if (!sub)
		return (NULL);
	while (i < len)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}
char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*strjoin;
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	strjoin = (char *)malloc(len + 1);
	if (!strjoin)
		return (NULL);
	while (s1[i] != '\0')
	{
		strjoin[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
		strjoin[i++] = s2[j++];
	strjoin[i] = '\0';
	return (strjoin);
}

char	*ft_strchr(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == (char)c)
			return ((char *)(str + i + 1));
		i++;
	}
	if ((char)c == '\0')
		return ((char *)(str + i));
	return (NULL);
}


char	*get_next_line(int fd)
{

	char	buffer[BUFFER_SIZE + 1];
	ssize_t char_read;
	ssize_t i;
	char	*line;
	static char	*storage;
	
	if(!storage)
		{
			storage = malloc(1);
			storage[0] = '\0';
		}

	while ((char_read = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[char_read] = '\0';
		char *temp = ft_strjoin(storage, buffer);
		if (!temp)
			return NULL;
		free(storage);
		storage = temp;
		i = 0;
		while (storage[i])
		{
			if(storage[i] == '.')	
			{
				line = ft_substr(storage, 0, i+1);
				char *rest = ft_substr(storage, i + 1, ft_strlen(storage) - i - 1);
				free(storage);
				storage = rest;
				return (line);
			}
			i++;
		}
	}
	if (storage && *storage)
	{
		line = ft_substr(storage, 0, ft_strlen(storage));
		free(storage);
		storage = NULL;
		return (line);
	}
	free(storage);
	storage = NULL;
	return NULL;
}



int main()
{
	int fd = open("text.txt", O_RDONLY);
	if (fd == -1)
		return (-1);
	char	*line = get_next_line(fd);
	while (line)
	{
		printf("\n => %s\n", line);
		free(line);
		line = get_next_line(fd);
	}
	return 0;
}