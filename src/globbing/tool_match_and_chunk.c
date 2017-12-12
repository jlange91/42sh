#include "../../inc/globbing.h"

void	ft_move_index(char **chunk_orig, int *count, char **tmp_orig, int flag)
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

int		ft_escape_or_end(char *tmp, char **chunk, int *count, int *escape)
{
	if (ft_strlen(tmp) == 0)
		return (1);
	else if ((*chunk)[0] == '\\' && (*chunk)[1] != '\\')
	{
		ft_move_index(chunk, count, NULL, 1);
		*escape = 1;
	}
	return (0);
}

int 	ft_skip_or_leave(char **tmp, char **chunk, int *count, int *escape)
{
	if ((*chunk)[0] == '?' && !(*escape))
		ft_move_index(chunk, count, NULL, 1);
	else if ((*chunk)[0] != (*tmp)[0])
		return (1);
	else
	{
		ft_move_index(chunk, count, tmp, 2);
		*escape = 0;
	}
	return (0);
}
