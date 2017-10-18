#include "../../inc/tree.h"
#include "../../inc/exec.h"
#include "../../inc/line_edition.h"
#include "../../inc/env_term.h"
#include "../../inc/built_in.h"

void    ft_init_command_intern(t_tree *tree, t_cmd *cmd, char *out, int type)
{
    t_tree  *tmp;
    int     i;

    tmp = tree;
    i = 0;
    cmd->type = -1;
    if (out)
    {
        cmd->type = type;
        cmd->str_type = out;
    }
    while (tmp && tmp->type == TOKEN_CMD)
    {
        tmp = tmp->right;
        i++;
    }
    if ((cmd->str_t = (char **)malloc(sizeof(char *) * (i + 1))) == NULL)
    {
        ft_putendl_fd("Error malloc", 2);
        exit(1);
    }
    i = 0;
    tmp = tree;
    while (tmp && tmp->type == TOKEN_CMD)
    {
        cmd->str_t[i] = ft_strdup(tmp->str);
        tmp = tmp->right;
        i++;
    }
    cmd->str_t[i] = NULL;
}

int    ft_execute_command_intern(t_cmd *cmd, t_env *env)
{
    int i;
    int ret;

    i = -1;
    ret = 0;
    if (cmd && cmd->str_t)
    {
        if (cmd->str_t[0] == NULL && cmd->str_type != NULL && cmd->type != -1)
        {
            if (!ft_cmd_exe(cmd->str_t[0], cmd, env))
                return (0);
        }
        while (cmd->str_t[++i])
        {
            ret = ft_check_builtin(cmd->str_t[0], env, cmd);
			cmd->str_t = ft_strsplit(env->line_str, ' ');
			if (ret == -1)
                return (0);
            else if (ret == 1)
                return (1);
            else
                if (!ft_cmd_exe(cmd->str_t[0], cmd, env))
                    return (0);
            break;
        }
    }
    return (1);
}

int    ft_execute_simple_command(int type, char *out, t_tree *root, t_env *env)
{
    t_cmd   cmd;

    ft_init_command_intern(root, &cmd, out, type);
    if (!ft_execute_command_intern(&cmd, env))
    {
        ft_free_tab(cmd.str_t);
        return (0);
    }
    else
        ft_free_tab(cmd.str_t);
    return (1);
}

int    ft_execute_command(t_tree *tree, t_env *env)
{
    if (tree && tree->type == TOKEN_R_R)
    {
        if (ft_execute_simple_command(tree->type, tree->str, tree->right, env))
            return (ft_execute_command(tree->left, env));
    }
    else
    {
        if (ft_execute_simple_command(-1, NULL, tree, env))
            return (1);
    }
    return (0);
}

int    ft_execute_job(t_tree *tree, t_env *env)
{
    if (ft_execute_command(tree, env))
        return (1);
    else
        return(0);
}

int    ft_execute(t_tree *tree, t_env *env, t_lexer *lexer)
{
    if (tree == NULL)        
        return (0);
    else if (tree && tree->type == TOKEN_MULTI_SEM)
    {
        if (!ft_execute_job(tree->left, env))
            return (0);
        return (ft_execute(tree->right, env, lexer));
    }
    else if (tree && tree->type == TOKEN_BACKGROUND)
    {
        if (!ft_execute_job(tree->left, env))
            return (0);
        return (ft_execute(tree->right, env, lexer));
    }
    return ((ft_execute_job(tree, env)));
}
