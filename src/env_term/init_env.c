#include "../../inc/env_term.h"

static	void	ft_shlv_bis(t_env *env, int *add)
{
    char		*res;

    res = NULL;
    res = ft_getenv("SHLVL", env);
    if (res != NULL)
    {
        *add = ft_atoi(res);
        free(res);
    }
}

static	void	ft_shlv(t_env *env)
{
    int			add;
    static int	count;
    char		*ret;

    add = 0;
    ret = NULL;
    if (count == 0)
    {
        ft_shlv_bis(env, &add);
        ret = ft_itoa(count + add + 1);
        ft_setenv("SHLVL", ret, env);
        free(ret);
    }
    else
    {
        ret = ft_itoa(count + add);
        ft_setenv("SHLVL", ret, env);
        free(ret);
    }
    count++;
}

static void		ft_basic_env(t_env **env)
{
    char			str[1024];
    t_env           *tmp;
    struct passwd   *user;
    uid_t           uid;

    tmp = NULL;
    ft_memset(str, '\0', sizeof(str));
    getcwd(str, sizeof(str));
    uid = getuid();
    user = getpwuid(uid);
    ft_cpy_env(&tmp, "HOME=", 0);
    ft_setenv("HOME", user->pw_dir, tmp);
    ft_setenv("PWD", str, tmp);
    ft_setenv("SHLVL", "0", tmp);
    ft_setenv("TERM", "xterm", tmp);
    *env = tmp;
}

t_env           *ft_init_env(char **env)
{
    t_env   *env_c;
    int     i;

    env_c = NULL;
    if (!(*env))
        ft_basic_env(&env_c);
    else
    {
        i = -1;
        while (env[++i])
            ft_cpy_env(&env_c, env[i], i);
        ft_shlv(env_c);
    }
    return (env_c);
}
