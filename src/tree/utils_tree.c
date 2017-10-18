#include "../../inc/tree.h"

void    ft_add_info_ast(t_tree *root, int type, char *str)
{
    if (root)
    {
        root->type = type;
        root->str = str;
    }
}

void    ft_add_node_ast(t_tree *root, t_tree *left, t_tree *right)
{
    if (root)
    {
        root->left = left;
        root->right = right;
    }
}

t_tree  *ft_init_tree(t_token *tmp, t_tree *job, t_tree *cmd, int type)
{
    t_tree  *root;

    root = NULL;
    if ((root = (t_tree *)malloc(sizeof(*root))) == NULL)
    {
        ft_putendl_fd("Error malloc", 2);
        exit(1);
    }
    if (tmp)
    {
        tmp->cmd[tmp->cmd_len] = 0;
        ft_add_info_ast(root, type, tmp->cmd);
        ft_add_node_ast(root, job, cmd);
    }
    return (root);
}

int     ft_find_token(t_token **current, int type, t_token **tmp)
{
    if (*current && (*current)->type == type)
    {
        *tmp = *current;
        *current = (*current)->next;
        return (1);
    }
    return (0);
}

void    ft_free_ast(t_tree *root)
{
    if (!root)
        return ;
    ft_free_ast(root->left);
    ft_free_ast(root->right);
    free(root);
}
