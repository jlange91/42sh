#include "../../inc/token.h"

void    ft_free_dlist_token(dtoken **token)
{
    t_token  *del;
    t_token  *elem;

    if ((*token)->begin)
    {
        elem = (*token)->begin;
        while (elem)
        {
            del = elem;
            elem = elem->next;
            free(del->cmd);
            free(del);
        }
        (*token)->begin = NULL;
        (*token)->end = NULL;
        return ;
    }
}

void    ft_fill_tabtoken(const char *tab_token[14], const char *basic_token[6])
{
    tab_token[TOKEN_DR_R] = ">>";
    tab_token[TOKEN_R_R] = ">";
    tab_token[TOKEN_DR_L] = "<<";
    tab_token[TOKEN_R_L] = "<";
    tab_token[TOKEN_BACK_R_R] = "&>";
    tab_token[TOKEN_QUOTE] = "`";
    tab_token[TOKEN_R_R_BACK] = ">&";
    tab_token[TOKEN_MULTI_SEM] = ";";
    tab_token[TOKEN_OR] = "||";
    tab_token[TOKEN_PIPE] = "|";
    tab_token[TOKEN_AND] = "&&";
    tab_token[TOKEN_BACKGROUND] = "&";
    tab_token[TOKEN_CMD] = "CMD";
    tab_token[TOKEN_EOL] = "EOF";
    basic_token[0] = ";";
    basic_token[1] = "|";
    basic_token[2] = ">";
    basic_token[3] = "<";
    basic_token[4] = "&";
    basic_token[5] = "`";
}

dtoken  *init_token(void)
{
    dtoken *new;

    if ((new = (dtoken *)malloc(sizeof(*new))) == NULL)
    {
		ft_putendl_fd("Error malloc", 2);
		return (NULL);
    }
    ft_fill_tabtoken(new->tab_token, new->basic_token);
    new->type = 0;
    new->begin = NULL;
    new->end = NULL;
    return (new);
}

t_lexer *init_lexer(void)
{
    t_lexer *lexer;

    lexer = NULL;
    if ((lexer = (t_lexer *)malloc(sizeof(*lexer))) == NULL)
    {
		ft_putendl_fd("Error malloc", 2);
		return (NULL);
    }
    if ((lexer->token = init_token()) == NULL)
		ft_putendl_fd("init_token", 2);
    lexer->str = NULL;
    return (lexer);
}
