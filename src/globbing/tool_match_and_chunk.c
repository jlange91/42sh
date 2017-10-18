#include "../../inc/globbing.h"

void	ft_move_letter_and_count(char **chunk_orig, int *count, char **tmp_orig, int flag)
{
	char 	*chunk;
	char	*tmp;

	if (flag == 1)
	{
		chunk = *chunk_orig;
		chunk++;
		(*count)++;
		*chunk_orig = chunk;
	}
	else if (flag == 2)
	{
		chunk = *chunk_orig;
		tmp = *tmp_orig;
		(*count)++;
		chunk++;
		tmp++;
		*tmp_orig = tmp;
		*chunk_orig = chunk;
	}
}

char	*ft_init_var(int *neg, int *count, int *match, char *word)
{
	char	*tmp;

	*neg = 1;
	*count = 0;
	*match = 0;
	tmp = word;
	return (tmp);
}
