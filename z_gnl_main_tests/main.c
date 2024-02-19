
#include "get_next_line.h" //malloc(ft_calloc) and read functions
#include <fcntl.h>         //open function
#include <stdio.h>         //printf function

int	main(void)
{
	int		fd;
    int     change;
	char	*next_line;
	int		count;

	count = 0;
	fd = open("test.txt", O_RDONLY);
	while (1)
	{
		next_line = get_next_line(fd);
		if (next_line == NULL)
			break ;
		count++;
		printf("[%d]: %s\n", count, next_line);
		free(next_line);
	}
	close(fd);
	return (0);
}
