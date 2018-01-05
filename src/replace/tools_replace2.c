#include "../../inc/globbing.h"
#include "../../inc/sh21.h"
#include "../../inc/line_edition.h"

void 	ft_add_space(char **line, char *s_line, char *word)
{
	int 	count;
	int 	i;
	char 	*str;

	count = 0;
	str = ft_strstr(s_line, word);
	if (str != NULL)
	{
		i = 0;
		while (str[i] && str[i] != ' ')
			i++;
		while (str[i] && str[i] == ' ')
		{
			count++;
			i++;
		}
	}
	while (count > 0)
	{
		*line = ft_free_join(*line, " ", 'L');
		count--;
	}
}

void ft_join_all(char *word, char **line_tmp, int ret)
{
	*line_tmp = (*line_tmp == NULL) ? ft_strdup(word) :
	ft_free_join(*line_tmp, word, 'L');
	if (ret && word)
		free(word);
}
