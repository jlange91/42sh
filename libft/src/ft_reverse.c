#include "../include/libft.h"

char 		*ft_reverse(char *str)
{
	int 	i;
	int 	j;

	j = ft_strlen(str);
	i = 0;
	while (i < j / 2)
	{
		ft_swap(&str[i], &str[j - i - 1]);
		i++;
	}
	return (str);
}
