#include "../../inc/token.h"

int    ft_print_msg_error(int type, const char *tab_token[14])
{
        ft_putchar('\n');
        ft_putstr("Syntax error near unexpected token `");
        ft_putstr((char *)tab_token[type]);
        ft_putstr("'");
        ft_putchar('\n');
        return (0);
}

int     ft_unexpected_token(t_token *begin, t_lexer *lexer)
{
    if (begin->type != TOKEN_CMD && !(begin->prev)
            && (begin->type == TOKEN_AND || begin->type == TOKEN_BACKGROUND
                || begin->type == TOKEN_OR || begin->type == TOKEN_MULTI_SEM
                || begin->type == TOKEN_PIPE))
        return (ft_print_msg_error(begin->type, lexer->token->tab_token));
    else if (begin->type != TOKEN_CMD && begin->next && (begin->next->type == TOKEN_AND
                || begin->next->type == TOKEN_BACKGROUND
                || begin->next->type == TOKEN_OR || begin->next->type == TOKEN_MULTI_SEM
                || begin->next->type == TOKEN_PIPE))
        return (ft_print_msg_error(begin->next->type, lexer->token->tab_token));

    return(1);
}

void     ft_check_token(t_lexer *lexer)
{
    t_token *begin;

    begin = NULL;
    begin = lexer->token->begin;
    lexer->token->type = 0;
    while (begin)
    {
        if (ft_unexpected_token(begin, lexer) == 0)
        {
            lexer->token->type = -1;
            break;
        }
        begin = begin->next;
    }
}
