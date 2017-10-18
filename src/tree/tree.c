#include "../../inc/tree.h"

t_tree  *ft_multi_sem(t_token *current)                                          /* <job> ; || && <command> */
{
    t_tree  *job;
    t_tree  *cmd;
    t_token *tmp;
    t_token *tmp_cur;
    int     ret;

    job = NULL;
    cmd = NULL;
    tmp = NULL;
    tmp_cur = NULL;
    tmp_cur = current;
    ret = 0;
    if ((job = ft_get_job_pipe(&tmp_cur)) == NULL)
        ret = 1;
    if (ret)
    {
        if ((job = ft_get_job(&current)) == NULL)
            return (NULL);
    }
    else
        current = tmp_cur;
    if (!ft_find_token(&current, TOKEN_MULTI_SEM, &tmp))
    {
        ft_free_ast(job);
        return (NULL);
    }
    if ((cmd = ft_get_cmdline(current)) == NULL)
    {
        ft_free_ast(job);
        return (NULL);
    }
    return (ft_init_tree(tmp, job, cmd, TOKEN_MULTI_SEM));
}

t_tree  *ft_only_sem(t_token *current)
{
    t_tree  *job;
    t_token *tmp;

    job = NULL;
    tmp = NULL;
    if ((job = ft_get_job(&current)) == NULL)
        return (NULL);
    if (!ft_find_token(&current, TOKEN_MULTI_SEM, &tmp))
    {
        ft_free_ast(job);
        return (NULL);
    }
    return (ft_init_tree(tmp, job, NULL, TOKEN_MULTI_SEM));
}

t_tree  *ft_multi_background(t_token *current)
{
    t_tree  *job;
    t_tree  *cmd;
    t_token *tmp;

    job = NULL;
    cmd = NULL;
    tmp = NULL;
    if ((job = ft_get_job(&current)) == NULL)
        return (NULL);
    if (!ft_find_token(&current, TOKEN_BACKGROUND, &tmp))
    {
        ft_free_ast(job);
        return (NULL);
    }
    if ((cmd = ft_get_cmdline(current)) == NULL)
    {
        ft_free_ast(job);
        return (NULL);
    }
    return (ft_init_tree(tmp, job, cmd, TOKEN_BACKGROUND));
}

t_tree  *ft_only_background(t_token *current)
{
    t_tree  *job;
    t_token *tmp;

    job = NULL;
    tmp = NULL;
    if ((job = ft_get_job(&current)) == NULL)
        return (NULL);
    if (!ft_find_token(&current, TOKEN_BACKGROUND, &tmp))
    {
        ft_free_ast(job);
        return (NULL);
    }
    return (ft_init_tree(tmp, job, NULL, TOKEN_BACKGROUND));
}

t_tree  *ft_nocmdline(t_token *current)
{
    t_tree  *node;
    t_token *tmp_cur;
    int     ret;

    node = NULL;
    tmp_cur = NULL;
    tmp_cur = current;
    ret = 0;
    if ((node = ft_get_job_pipe(&tmp_cur)) == NULL)
        ret = 1;
    if (ret)
    {
        if ((node = ft_get_job(&current)) == NULL)
            return (NULL);
    }
    return (node);
}

t_tree  *ft_get_cmdline(t_token *current)
{
    t_tree  *node;

    node = NULL;
    if ((node = ft_multi_sem(current)) != NULL)
        return (node);
    if ((node = ft_only_sem(current)) != NULL)
        return (node);
    if ((node = ft_multi_background(current)) != NULL)
        return (node);
    if ((node = ft_only_background(current)) != NULL)
        return (node);
    if ((node = ft_nocmdline(current)) != NULL)
        return (node);
    return (NULL);
}

void    ft_parse(t_lexer *lexer, t_tree **root)
{
    t_token     *current;

    current = NULL;
    current = lexer->token->begin;
    *root = ft_get_cmdline(current);
}
