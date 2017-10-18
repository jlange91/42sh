#include "../../inc/env_term.h"

int		ft_free(char **str, int flag)
{
	int i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	if (flag == 1)
		return (1);
	else
		return (0);
}

int		ft_free_str(char *s1, char *s2, int flag)
{
	if (flag == 1)
	{
		if (s1)
			free(s1);
		if (s2)
			free(s2);
	}
	else
	{
		if (s1)
			free(s1);
	}
	return (0);
}
