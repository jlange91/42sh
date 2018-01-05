#include "../include/libft.h"

void 		ft_swap(char *a, char *b)
{
	char 	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}
