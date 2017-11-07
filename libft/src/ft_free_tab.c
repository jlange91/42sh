#include "../include/libft.h"

void    ft_free_tab(char **str)
{
    int i;

    if (str)
    {
        i = 0;
        while (str[i] != NULL)
        {
			free(str[i]);
            i++;
        }
        free(str);
    }
}
