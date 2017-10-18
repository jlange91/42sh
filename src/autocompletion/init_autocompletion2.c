#include "../../inc/autocompletion.h"

void    ft_init_autocompl_binary(t_shell *shell)
{
    int             i;
    DIR             *path;
    struct dirent   *file;

    i = 1;
    if ((path = opendir("/usr/bin/")) != NULL)
    {
        while ((file = readdir(path)) != NULL)
            if (file->d_name[0] != '.')
                ft_fill_back_autocompl(shell->autocompl_binary, file->d_name, i++);
        closedir(path);
    }
}
