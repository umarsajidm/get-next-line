// #include "get_next_line.h"
#include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>


# ifndef BUFFER_SIZE
# define BUFFER_SIZE 20
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



char	*get_next_line(int fd)
{

	char	buffer[BUFFER_SIZE + 1];
	ssize_t char_read;
	ssize_t i = 0;
	char	*string;
	char	*line;
	static char	*storage;
	
	
	line = malloc(1);
	if(!storage)
		{
			storage = malloc(1);
			storage[0] = '\0';
		}
	line[0] = '\0';

	char_read = read(fd, buffer, BUFFER_SIZE);
	if (char_read <= 0)
		return (NULL);
	while (char_read) 
	{
		buffer[char_read] = '\0';
		storage = ft_strjoin(storage, buffer);
		while(storage[i])
		{
			
			if(storage[i] == '.')
			{
				line = ft_substr(storage, 0, i+1);
				break;
			}
			i++;
		}
		char_read = read(fd, buffer, BUFFER_SIZE);
	}

	return line;
}



int main()
{
	int fd = open("text.txt", O_RDONLY);
	if (fd == -1)
		return (-1);
	char	*line = get_next_line(fd);

	while (line)
	{
		printf("%s\n =>\n", line);
	
		free(line);
		line = get_next_line(fd);
	}
	return 0;
}