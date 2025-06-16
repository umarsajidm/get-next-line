//#include "get_next_line.h"
#include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>


// // char	*get_next_line(int fd);

int putstr(char *str)
{
    int i;

    i = 0;
    if (!str)
        return (-1);
    while (str[i])
        write(1, &str[i++], 1);
    str[i] = '\0';
   // write(1, "\n", 1);
    return (i);
}
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



int main()
{
    char buffer[900];
    int i = 0;
    int byte_read;
    char *string;
    int j = 0;


    int fd = open("text.txt", O_RDONLY);
    if (fd == -1)
        return (-1);

    byte_read = read(fd, buffer, 500);
    buffer[byte_read] = '\0';

	while (buffer[i])
{
	if (buffer[i] == '.')
	{
		string = ft_substr(buffer, j, i - j + 1);
		putstr(string);
		write(1, "\n", 1);
		free(string);
		j = i + 1;
	}
	i++;
}
    close(fd);
    return 0;
}



