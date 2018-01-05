#include "../include/libft.h"
#include <fcntl.h>

int     ft_count_from_file(char *path)
{
    int     fd;
    int     count;
    int     ret;
    char    *line;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (-1);
	line = NULL;
    count = 0;
    while ((ret = get_next_line(fd, &line)) > 0)
	{
        count++;
		free(line);
	}
    close(fd);
    return (count);
}
