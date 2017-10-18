#include "../../inc/exec.h"

void            ft_free_all_cmd(char **env_tab, char **argv)
{
    if (env_tab)
        ft_free_tab(env_tab);
    if (argv)
	    ft_free_tab(argv);
}

static int     ft_count_env(t_env *env)
{
    int     count;

    count = 0;
    while (env)
    {
        count++;
        env = env->next;
    }
    return (count);
}

char    **ft_env_to_tab(t_env *env)
{
    char    **dstr;
    int     i;

    dstr = NULL;
    if ((dstr = (char **)malloc(sizeof(char *) * (ft_count_env(env) + 1))) == NULL)
    {
        ft_putendl_fd("Error malloc", 2);
        return (NULL);
    }
    i = 0;
    while (env)
    {
        dstr[i++] = ft_strdup(env->line_env);
        env = env->next;
    }
    dstr[i] = NULL;
    return (dstr);
}

char    **ft_cmd_to_tab(t_cmd *cmd)
{
    char    **dstr;
    int     i;

    dstr= NULL;
    if ((dstr = (char **)malloc(sizeof(char *) * (ft_count_dtab(cmd->str_t) + 1))) == NULL)
    {
        ft_putendl_fd("Error malloc", 2);
        return (NULL);
    }
    i = -1;
    while (cmd->str_t[++i])
        dstr[i] = ft_strdup(cmd->str_t[i]);
    dstr[i] = NULL;
    return (dstr);
}
