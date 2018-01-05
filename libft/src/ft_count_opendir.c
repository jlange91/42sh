#include "../include/libft.h"
#include <dirent.h>

int  ft_count_opendir(char *str)
{
	int             count;
	DIR             *path;
	struct dirent   *file;

	count = 0;
	if ((path = opendir(str)) != NULL)
	{
		while ((file = readdir(path)) != NULL)
			count++;
		closedir(path);
	}
	return (count);
}
