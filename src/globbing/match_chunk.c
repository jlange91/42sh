#include "../../inc/globbing.h"

static void	ft_is_neg(char **chunk, int *neg)
{
	char	*tmp;

	tmp = *chunk;
	tmp++;
	if (*tmp == '^')
	{
		tmp++;
		*neg = 0;
	}
	*chunk = tmp;
}

static int	ft_between(char *chunk, char *lo, char *hi, int *count)
{
	int 	i;
	int		flag;
	char	*tmp;

	i = 0;
	flag = 0;
	tmp = chunk;
	while (tmp[i] && tmp[i] != ']')
	{
		if (tmp[i] == '-') 
		{
			(*count)++;
			flag = 1;
			break;
		}
		i++;
	}
	if (flag)
	{
		*lo = tmp[i - 1];
		*hi = tmp[i + 1];
		return (1);
	}
	return (0);
}

static int	ft_suite_match_chunk_split(char **chunk_orig, int match, int neg, int *count)
{
	char *chunk;

	chunk = *chunk_orig;
	if (match != neg)
		return (0);
	if (neg == 0)
		(*count)++;
	if (chunk[0] != ']')
		while (ft_strlen(chunk) > 0)
		{
			if (chunk[0] == ']')
			{
				chunk++;
				break;
			}
			chunk++;
		}
	*chunk_orig = chunk;
	return (1);
}

static void	ft_match_chunk_split(char **chunk_orig, int *match, char *tmp, int *count)
{
	char	l;
	char	h;
	char	*chunk;

	chunk = *chunk_orig;
	while (ft_strlen(chunk) > 0)
	{
		if (!ft_between(chunk, &l, &h, count))
		{
			l = chunk[0];
			h = l;
		}
		if (chunk[0] == ']')
		{
			chunk++;
			break;
		}
		if (l <= tmp[0] && tmp[0] <= h)
		{
			(*count)++;
			*match = 1;
			break;
		}
		chunk++;
	}
	*chunk_orig = chunk;
}

int	ft_match_chunk(char *chunk, char **word, int i)
{
	char    *tmp;
	int     count;
	int     match;
	int     neg;

	tmp = ft_init_var(&neg, &count, &match, *word) + i;
	while (ft_strlen(chunk) > 0)
		if (ft_strlen(tmp) == 0)
			return (0);
		else if (chunk[0] == '[')
		{
			ft_is_neg(&chunk, &neg);
			ft_match_chunk_split(&chunk, &match, &tmp[0], &count);
			if (!ft_suite_match_chunk_split(&chunk, match, neg, &count))
				return (0);
		}
		else if (chunk[0] == '?' || (chunk[0] == '\\' && chunk[1] != '\\'))
			ft_move_letter_and_count(&chunk, &count, NULL, 1);
		else if (chunk[0] != tmp[0])
			return (0);
		else
			ft_move_letter_and_count(&chunk, &count, &tmp, 2);
	*word = *word + i + count;
	return (1);
}
