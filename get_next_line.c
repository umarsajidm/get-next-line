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

// // char	*get_next_line(int fd)
// // {
	
// // }


int main()
{
    char buffer[900];
    int i = 0;
    int byte_read;
    char line[500];
    int j = 0;
 
    
    int fd = open("text.txt", O_RDONLY);
    if (fd == -1)
        return (-1);

    byte_read = read(fd, buffer, 500);
    buffer[byte_read] = '\0';
    while (buffer[i] && byte_read > 0)
    {
        if (buffer[i] == '\n')
        {
            while (j < i)
                {
                line[j] = buffer[j];
                j++;
                }
            line[j] = '\0';
            break;
        }
        i++;            
    }

    close(fd);
    

    printf("%s", line);
    return 0;

}


