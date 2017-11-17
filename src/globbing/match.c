#include "../../inc/globbing.h"

static char		*ft_get_next_pattern(char **pattern, int *star, int *bracket)
{
	int		i;
	int		leave;
	char	*chunk;

	if (ft_strlen(*pattern) > 0)
	{
		chunk = NULL;
		if ((chunk = (char *)malloc(sizeof(char) * (ft_strlen(*pattern) + 1))) == NULL)
			return (NULL);
	}
	if  (ft_strlen(*pattern) > 0 && *(pattern[0]) == '*')
	{
		(*pattern)++;
		*star = 1;
	}
	i = -1;
	leave = 0;
	while (ft_strlen(*pattern) > 0)
	{
		if (**pattern == '[')
			*bracket = 1;
		if (**pattern == ']')
			*bracket = 0;
		if (**pattern == '-')
			leave = 1;
		if (**pattern == '*')
		{
			leave = 0;
			if (!(*bracket))
				break;
		}
		chunk[++i] = **pattern;
		(*pattern)++;
	}
	chunk[++i] = '\0';
	if (leave != 0)
	{
		free(chunk);
		chunk = NULL;
	}
	return (chunk);
}

static int ft_match_split(char *pattern, char *word, char *chunk)
{
	int i;

	i = 0;
	while (i < (int)ft_strlen(word))
	{
		if (ft_match_chunk(chunk, &word, i))
		{
			if (ft_strlen(pattern) == 0 && ft_strlen(word) > 0)
				continue;
			free(chunk);
			return (ft_match(pattern, word));
		}
		i++;
	}
	free(chunk);
	return (0);
}

int	ft_match(char *pattern, char *word)
{
	char	*chunk;
	int		star;
	int		inbracket;

	star = 0;
	inbracket = 0;
	while (ft_strlen(pattern) > 0)
	{
		if ((chunk = ft_get_next_pattern(&pattern, &star, &inbracket)) == NULL)
			return (0);
		if (star && *chunk == '\0')
		{
			free(chunk);
			return (1);
		}
		if (star)
			return (ft_match_split(pattern, word, chunk));
		if (ft_match_chunk(chunk, &word, 0))
		{
			free(chunk);
			continue;
		}
		free(chunk);
		return (0);
	}
	return (ft_strlen(word) == 0);
}
