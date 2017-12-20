#include "../include/libft.h"

int ft_only_digit(char *av)
{
	int i;

	i = 0;
	while (av[i] && av[i] == '-')
		i++;
	while (av[i] && ft_isdigit(av[i]))
		i++;
	if (i == ft_strlen(av))
		return (1);
	return (0);
}
