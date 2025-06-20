# include <stdlib.h>
# include <unistd.h>

#  define BUFFER_SIZE 5

size_t	ft_strlen(char *str)
{
	size_t	count;

	count = 0;
	if (!str)
		return (count);
	while (str[count])
		count++;
	return (count);
}

char	*ft_strchr(const char *str, int c)
{
	if (!str)
		return (NULL);
	while (*str)
	{
		if (*str == c)
			return ((char *)str);
		str++;
	}
	if (c == '\0')
		return ((char *)str);
	return (NULL);
}

char	*ft_strjoin(char *str1, char *str2)
{
	size_t	l1;
	size_t	l2;
	char	*join;
	size_t	i;

	if (!str1 && !str2)
		return (NULL);
	l1 = ft_strlen(str1);
	l2 = ft_strlen(str2);
	join = malloc(sizeof(char) * (l1 + l2 + 1));
	if (!join)
		return (NULL);
	i = 0;
	while (i < l1)
	{
		join[i] = str1[i];
		i++;
	}
	while (i < l1 + l2)
	{
		join[i] = str2[i - l1];
		i++;
	}
	join[l1 + l2] = '\0';
	return (join);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	n;
	size_t	max;

	if (!s)
		return (NULL);
	max = ft_strlen((char *)s);
	if (start >= max)
		len = 0;
	if (start + len > max)
		len = max - start;
	sub = malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (NULL);
	n = 0;
	while (s[start + n] && n < len)
	{
		sub[n] = s[start + n];
		n++;
	}
	sub[n] = '\0';
	return (sub);
}

static char	*ft_read_buffer(int fd, char *left_c)
{
	ssize_t		bytes_read;
	char		*buffer;
	char		*temp;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	// if (!buffer)
	// 	return (free(left_c), NULL);
	bytes_read = 1;
	temp = NULL;
	while (!left_c || (!ft_strchr(left_c, '\n') && bytes_read > 0))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		// if (bytes_read < 0)
		// 	return (free(buffer), free(left_c), NULL);
		// if (bytes_read == 0)
		// 	break ;
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(left_c, buffer);
		// if (!temp)
		// 	return (free(buffer), free(left_c), NULL);
		// free(left_c);
		left_c = temp;
	}
	return (free(buffer), left_c);
}

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*line;
	char		*temp;
	size_t		i;

	// if (fd < 0 || BUFFER_SIZE <= 0)
	// 	return (NULL);
	remainder = ft_read_buffer(fd, remainder);
	// if (!remainder || !remainder[0])
	// 	return (free(remainder), remainder = NULL, NULL);
	i = 0;
	while (remainder[i] && remainder[i] != '\n')
		i++;
	if (remainder[i] == '\n')
		i++;
	line = ft_substr(remainder, 0, i);
	// if (!line)
	// // 	return (free(remainder), remainder = NULL, NULL);
	// temp = ft_substr(remainder, i, ft_strlen(remainder) - i);
	// free (remainder);
	// remainder = temp;
	// if (!remainder || !*remainder)
	// 	return (free (remainder), remainder = NULL, line);
	return (line);
}

#include <fcntl.h>   // for open
#include <stdio.h>   // for printf
#include <stdlib.h>  // for free

char *get_next_line(int fd); // declare your function

int main(void)
{
	int fd = open("text.txt", O_RDONLY);
	if (fd == -1)
        return -1;

	char *line;
	while ((line = get_next_line(fd)))
	{
		printf("%s", line); // don't add newline because line may already include it
		free(line);
	}
	close(fd);
	return (0);
}

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
