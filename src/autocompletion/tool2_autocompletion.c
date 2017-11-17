#include "../../inc/autocompletion.h"

/*
 * * FUNCTION ADD "/" to shell_line 
 * if line from shell_line is dir
 *
 * We split the line for get last word and check if is dir;
 */
void    ft_check_is_dir(t_termc *shell)
{
    int         i;
    char        **tab_word;
    char        *tmp;
    struct stat info;

    tmp = ft_to_str(shell);
    tab_word = ft_strsplit2(tmp);
    free(tmp);
    i = ft_count_dtab(tab_word) - 1;
    ft_memset(&info, 0, sizeof(struct stat));
    stat(tab_word[i], &info);
    if (S_ISDIR(info.st_mode) && shell->line->end->c != '/'
            && shell->line->end->c != ' ')
        ft_fill_back_dlst(shell->line, '/', 0 + 2);
    ft_free_tab(tab_word);
}

void    ft_cpy_autocompl_to_lineshell(t_termc *shell)
{
    int i;
    int j;

    i = -1;
    j = 0;
    if (shell->autocompl->str != NULL)
    {
        j = ft_strlen(shell->autocompl->str) - 1;
        while (shell->autocompl->str[j] != '/' && shell->autocompl->str[j] != ' ')                             //REMOVE LAST LETTER AFTER / FOR REPLACE
            j--;
        j++;
        while (shell->autocompl->str[++i] && i < j)
            ft_fill_back_dlst(shell->line, shell->autocompl->str[i], i + 2);
    }
    ft_check_is_dir(shell);
    i = -1;
    while (shell->autocompl->current->data[++i])
        ft_fill_back_dlst(shell->line, shell->autocompl->current->data[i], i + 2);
}

char    *ft_antislash_here_bis(int limit, int len, char *str)
{
    char	*new;
    int     j;

    if ((new = (char *)malloc(sizeof(char) * ((ft_strlen(str) - len) + 1))) == NULL)
    {
        ft_putendl_fd("error malloc", 2);
        return (NULL);
    }
    j = -1;
    while (str[++j])
    {
        if (j == limit)
        {
            if (j == 0)
            {
                new[j] = str[j];
                j++;
            }
            break;
        }
        new[j] = str[j];
    }
    new[j] = '\0';
    return (new);
}

int    ft_reset(t_termc *shell, char **env)
{
    tputs(shell->term->cdstr, 1, ft_inputstr);
    if (shell->autocompl->str != NULL)
    {
        free(shell->autocompl->str);
        shell->autocompl->str = NULL;
    }
    shell->auto_active = 1;
    shell->history->active = 0;
    shell->line->last = 1;
    if (shell->autocompl->finish == 1)
        shell->autocompl->finish = 0;
    if (ft_count_dlnk(shell) == 0)
    {
        ft_init_simple_autocompl(shell, env);
        return (1);
    }
    return (0);
}

void    ft_put_antislash_one_word(t_termc *shell)
{
    char        *tmp;
    struct stat info;

    tmp = NULL;
    ft_memset(&info, 0, sizeof(struct stat));
    stat(shell->autocompl->str, &info);
    if (S_ISDIR(info.st_mode) == 1
            && shell->autocompl->str[ft_strlen(shell->autocompl->str) - 1] != '/')
    {
        tmp = ft_strdup(shell->autocompl->str);
        free(shell->autocompl->str);
        shell->autocompl->str = ft_strjoin(tmp, "/");
        free(tmp);
    }
}
