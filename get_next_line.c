//#include "get_next_line.h"
#include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# define BUFFER_SIZE 5


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

int one_string(int fd)
{
	char	*string;
	char	*storage;
	char	buffer[BUFFER_SIZE + 1];
	ssize_t		read_char;
	ssize_t		i = 0;
	ssize_t		j = 0;

	storage = malloc(1);
	if (!storage)
		return (-1);
	storage[0] = '\0';
	
	while ((read_char = read(fd, buffer, BUFFER_SIZE))> 0)
	{
		if (read_char < 0)
			return (-1);
		buffer[read_char] = '\0';
		string = ft_strdup(buffer);
		char *temp = storage;
		storage = ft_strjoin(storage, string);
		while(storage[i])
		{
			if (storage[i] == '\n')
				{
					string = ft_substr(storage, j, i-j+1);
					j = i + 1;
					printf("\n =>%s\n", string);
					free(string);
				}
			i++;
		}
		free(string);
		free(temp);
	}
	
	free(storage);
	return 0;
}
int main()
{
	int fd = open("text.txt", O_RDONLY);
	if (fd == -1)
		return -1;
	one_string(fd);
	return 0;
}
