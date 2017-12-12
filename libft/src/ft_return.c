#include "../include/libft.h"

int ft_returnfree(char *str, int ret, char c)
{
    if (c == 'f')
    {
        if (str)
            free(str);
    }
    return (ret);
}
