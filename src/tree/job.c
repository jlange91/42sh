#include "../../inc/tree.h"

t_tree  *ft_otherargv1(t_token **current)
{
   t_tree   *token; 
   t_token  *tmp;

   tmp = NULL;
   if (!ft_find_token(current, TOKEN_CMD, &tmp))
       return (NULL);
   token = ft_otherargv(current);
   return (ft_init_tree(tmp, NULL, token, TOKEN_CMD));
}

t_tree  *ft_otherargv(t_token **current)
{
    t_tree  *node;
    t_token *tmp;

    node = NULL;
    tmp = *current;
    if ((node = ft_otherargv1(&tmp)) != NULL)
    {
        *current = tmp;
        return (node);
    }
    return (NULL);
}

t_tree  *ft_get_job_pipe(t_token **current)
{
    t_tree  *cmd;
    t_tree  *job;
    t_token *tmp;

    cmd = NULL;
    job = NULL;
    tmp = NULL;
    if ((cmd = ft_get_job(current)) == NULL)
        return (NULL);
    if (!ft_find_token(current, TOKEN_PIPE, &tmp))
    {
        ft_free_ast(cmd);
        return (NULL);
    }
    if (tmp)
        tmp = tmp->next;
    if ((job = ft_get_job(current)) == NULL)
    {
        ft_free_ast(cmd);
        return (NULL);
    }
    return (ft_init_tree(tmp, cmd, job, TOKEN_PIPE));
}

t_tree  *ft_only_cmd(t_token **current)
{
    t_tree  *token;
    t_token *tmp;

    tmp = NULL;
    if ((!ft_find_token(current, TOKEN_CMD, &tmp)))
        return (NULL);
    token = ft_otherargv(current);
    return (ft_init_tree(tmp, NULL, token, TOKEN_CMD));
}

t_tree  *ft_command_red(t_token **current)
{
    t_tree  *node;
    t_token *tmp;

    tmp = *current;
    if ((node = ft_greater_cmd(&tmp)) != NULL)
    {
        *current = tmp;
        return (node);
    }
    return (NULL);
}

t_tree  *ft_greater_cmd(t_token **current)
{
    t_tree  *token;
    t_tree  *node;
    t_token *tmp;

    tmp = NULL;
    node = ft_only_cmd(current);
    if (!ft_find_token(current, TOKEN_R_R, &tmp))
        return (NULL);
    if (*current)
        while (*current && (*current)->type == TOKEN_CMD)
            *current = (*current)->next;
    if (tmp && tmp->next)
        tmp = tmp->next;
    token = ft_command_red(current);
    return (ft_init_tree(tmp, token, node, TOKEN_R_R));
}

/*FT_PUTCOMMAND*/
/*
 * * add last SON we add str ==> command
 *
 */

void    ft_putcommand(t_tree **tree)
{
    t_tree  *tree_tmp;
    t_tree  *tmp_node;
    t_tree    *new;

    if ((new = (t_tree *)malloc(sizeof(*new))) == NULL)
    {
        ft_putendl_fd("Error malloc", 2);
        exit(0);
    }
    new->str = ft_strdup((*tree)->right->str);
    new->type = TOKEN_CMD;
    new->right = NULL;
    new->left = NULL;
    tree_tmp = *tree;
    while (tree_tmp)
    {
        tmp_node = tree_tmp;
        free(tree_tmp->right);
        tree_tmp->right = NULL;
        tree_tmp = tree_tmp->left;
        if (!tree_tmp)
            tmp_node->right = new;
    }
}

t_tree  *ft_get_job(t_token **current)
{
    t_tree  *node;
    t_token *tmp;

    node = NULL;
    /*tmp = *current;
    if ((node = ft_command_red(&tmp)) != NULL)
    {
        *current = tmp;
        ft_putcommand(&node);
        return (node);
    }*/
    tmp = *current;
    if ((node = ft_only_cmd(&tmp)) != NULL)
    {
        *current = tmp;
        return (node);
    }
    return (NULL);
}
