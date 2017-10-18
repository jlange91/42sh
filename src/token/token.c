#include "../../inc/token.h"

int     ft_len_cmd(char *str, dtoken *t)
{
    int i;
    int j;

    i = -1;
    while (str[++i])
    {
        j = -1;
        while (++j < 6)
            if (str[i] == t->basic_token[j][0] || !str[i] || str[i] == ' '
                    || str[i] == '\t')
                return (i);
    }
    return (i);
}

int     ft_token_here(t_token *token, char *str, dtoken *t)
{
    int         ret;

    ret = 2;
    if (!str[1] || str[1] == ' ' || str[1] == '\t')
        ret = 1;
    token->type = -1;
    while (++token->type < 12)
        if (ft_strncmp(t->tab_token[token->type], str, ret) == 0
                && ft_strlen(t->tab_token[token->type]) == (size_t)ret)
            return (ft_strlen(t->tab_token[token->type]));
    token->type = -1;
    while (++token->type < 12)
        if (str[0] == t->tab_token[token->type][0] && str[1] != t->tab_token[token->type][1])
            return (1);
    return (ft_len_cmd(str, t));
}

int    ft_fill_dlnk_token(t_lexer *lexer, int i, dtoken *token)
{
    t_token *new;

    new = NULL;
    if ((new = (t_token *)malloc(sizeof(*new))) == NULL)
    {
        ft_putendl_fd("Error malloc", 2);
        exit(1);
    }
    new->cmd = ft_strdup(&(lexer)->str[i]);
    new->type = -1;
    new->pos = 0;
    new->cmd_len = ft_token_here(new, &(lexer)->str[i], token);
    new->next = NULL;
    new->prev = token->end;
    if (token->end)
        token->end->next = new;
    else
        token->begin = new;
    token->end = new;
    return (i + new->cmd_len);
}

dtoken     *ft_parse_token(char *str, t_lexer *lexer)
{
    int i;

    i = 0;
    lexer->str = str;
    if (ft_strlen(lexer->str) == 0)
    {
        lexer->token->type = -1;
        return (lexer->token);
    }
    else
    {
        while (lexer->str[i])
        {
            if (lexer->str[i] && (lexer->str[i] == ' ' || lexer->str[i] == '\t'))
                i++;
            else
                i = ft_fill_dlnk_token(lexer, i, lexer->token);
        }
    }
    ft_check_token(lexer);
    return (lexer->token);
}
