#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"
int main(void)
{
    char    *line1;
    char    *line2;
    int     fd1;
    int     fd2;
    int     i;

	fd1 = open("./test.txt", O_RDONLY);
    fd2 = open("./test2.txt", O_RDONLY);
    line1 = get_next_line(fd1);
    line2 = get_next_line(fd2);
    i = 0;
    while (line1 || line2)
    {
        printf("test.txt - %d call : |%s|\n", ++i, line1);
        printf("test2.txt - %d call : |%s|\n", i, line2);
        // if (i == 2)
        // {
            // close(fd2);
            // fd2 = -1;
        // }
        free(line1);
        free(line2);
        line1 = get_next_line(fd1);
        line2 = get_next_line(fd2);
    }
    close(fd1);
    close(fd2);
    system("leaks a.out");
    return(0);
}

//gcc -Wall -Werror -Wextra -D BUFFER_SIZE = 42 get_next_line.c get_next_line_utils.c main.c
