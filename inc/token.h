#ifndef TOKEN_H
# define TOKEN_H

#include "sh21.h"

/**************************************************************/
/*TOKEN.C*/

dtoken         *ft_parse_token(char *str, t_lexer *lexer);

/**************************************************************/
/*LEXER.C*/
t_lexer     *init_lexer(void);
void        ft_free_dlist_token(dtoken **token);

/**************************************************************/
/*UTILS_TOKEN.C*/
void         ft_check_token(t_lexer *lexer);

#endif 
