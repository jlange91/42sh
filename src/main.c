# include "../inc/sh21.h"
# include "../inc/env_term.h"
# include "../inc/line_edition.h"
# include "../inc/token.h"

void    freeViteFait(t_env **env)
{
    t_env   *tmp;
    t_env   *del;

    del = NULL;
    tmp = NULL;
    tmp = *env;
    while (tmp)
    {
        del = tmp;
        tmp = tmp->next;
        free(del->line_env);
        free(del);
    }
    free(tmp);
    tmp = NULL;
}

void    ft_free_a(t_env *env, t_shell *shell, t_lexer *lexer)
{
    ft_free_dlist_token(&(lexer)->token);
    free(lexer->token);
    free(lexer);
    freeViteFait(&env);
	ft_free_all(shell);
}

int     main(int ac, char **av, char **env)
{
    t_env   *env_c;
	t_shell *shell;
    t_lexer *lexer;

    (void)ac;
    (void)av;
	shell = NULL;
    env_c = ft_init_env(env);
	shell = init_shell(env_c);
    lexer = init_lexer();
    ft_line_edition(env_c, shell, lexer);
    ft_free_a(env_c, shell, lexer);
    return (0);
}
