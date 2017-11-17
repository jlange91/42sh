#include "../../inc/globbing.h"
#include "../../inc/autocompletion.h"

static int  ft_good_syntax(char **str_tab)
{
    int i;
    int j;
    int count;
    int count2;

    i = -1;
    count = 0;
    count2 = 0;
    while (str_tab[++i])
    {
        j = -1;
        while (str_tab[i][++j])
        {
            if (str_tab[i][j] == '[')
                count++;
            if (str_tab[i][j] == ']')
                count2++;
        }
    }
    if (count == count2)
        return (1);
    return (0);
}

static int  ft_count_glob(char **str_tab)
{
    int i;
    int j;
    int count;

    i = -1;
    count = 0;
    while (str_tab[++i])
    {
        j = -1;
        while (str_tab[i][++j])
        {
            if (str_tab[i][j] == '*' || str_tab[i][j] == '[' || str_tab[i][j] == '?')
            {
                count++;
                break;
            }
        }
    }
    return (count);
}

int  ft_glob_here(char *str)
{
    int i;

    i = -1;
    while (str[++i])
        if (str[i] == '*' || str[i] == '?'
                || str[i] == '[')
            return (1);
    return (0);
}

static char **ft_fill_tab(char **str_tab, int count, char **env, t_glob *glob)
{
    char    **new_tab;

	(void)count;
    new_tab = NULL;
    new_tab = ft_result(env, glob, str_tab);
    return (new_tab);
}

int        ft_get_glob(t_glob **glob, char **str_tab, char **env)
{
    int count;

    count = 0;
    if ((count = ft_count_glob(str_tab)) == 0)
        return (0);
    if (ft_good_syntax(str_tab))
	{
        if (((*glob)->tab_str = ft_fill_tab(str_tab, count, env, *glob)) != NULL)
			return (1);
	}
    else
    {
        ft_putchar('\n');
        ft_putendl_fd("Bad pattern", 2);
    }
	return (0);
}
