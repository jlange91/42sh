#include "../../inc/globbing.h"
#include "../../inc/sh21.h"
#include "../../inc/line_edition.h"

static inline char 		*ft_get_word(t_termc *tsh, t_lineterm *end)
{
	char 		*word;
	t_lineterm	*begin_t;

	word = NULL;
	begin_t = tsh->line->begin;
	begin_t = ft_dontGetPrompt2(begin_t);
	ft_join_all(&end->c, &word, 0);
	while (begin_t && begin_t != end)
		begin_t = begin_t->next;
	while (end && (end = end->prev) && end->c != ' ')
		ft_join_all(&end->c, &word, 0);
	ft_reverse(word);
	while (begin_t && (begin_t = begin_t->next) && begin_t->c != ' ')
		ft_join_all(&end->c, &word, 0);
	if (!ft_glob_here(word) && !ft_strchr(word, '$') && !ft_strchr(word, '~'))
	{
		free(word);
		return (NULL);
	}
	return (word);
}

static inline int ft_repl_expand(t_termc *tsh, dlist *tmp, char *word, int *ret)
{
	int 		i;
	t_lineterm 	*begin;
	t_shell 	*sh;

	if (ft_glob_here(word) || (!ft_strchr(word, '$') && !ft_strchr(word, '~')))
		return (0);
	sh = ft_ret_sh(NULL);
	sh->line = ft_strdup(word);
	ft_replace(sh);
	i = ft_strlen(word);
	begin = tmp->begin;
	if (!(*ret) && ft_strcmp(sh->line, word) != 0 && ft_strlen(sh->line) > 0 &&
			ft_word_here(begin, word))
	{
		*ret = 1;
		ft_cpy_to_line(sh->line, tsh);
		while (tmp->begin && i > 0)
		{
			i--;
			tmp->begin = tmp->begin->next;
		}
		tsh->repl = 1;
		tsh->keyflag->k_tab = 0;
		return (ft_returnfree(sh->line, 1, 'f'));
	}
	return (ft_returnfree(sh->line, 0, 'f'));
}

static inline int ft_repl_glob(t_termc *tsh, dlist *tmp, char *word, int *ret)
{
	int 		i;
	char		*glob;
	t_lineterm 	*begin;

	glob = NULL;
	i = 0;
	if (ft_glob_here(word))
		glob = ft_glob(word);
	i = ft_strlen(word);
	begin = tmp->begin;
	if (!(*ret) && glob != NULL && tmp->begin->c == word[0] &&\
			ft_word_here(begin, word))
	{
		*ret = 1;
		tsh->keyflag->k_tab = 0;
		tsh->repl = 1;
		ft_cpy_to_line(glob, tsh);
		while (tmp->begin && i > 0)
		{
			i--;
			tmp->begin = tmp->begin->next;
		}
		return (ft_returnfree(glob, 1, 'f'));
	}
	return (ft_returnfree(glob, 0, 'f'));
}

static inline void 		ft_split_repl(t_termc *tsh, dlist tmp, char *word)
{
	int 	ret;

	ret = 0;
	while (tmp.begin)
	{
		if (tmp.begin->c == word[0])
		{
			if (!ft_repl_glob(tsh, &tmp, word, &ret) &&\
					!ft_repl_expand(tsh, &tmp, word, &ret))
			{
				push_dupdlst(tsh->line, tmp.begin->c, tmp.begin->s_pos,\
						tmp.begin->index);
				tmp.begin = tmp.begin->next;
			}
		}
		else
		{
			push_dupdlst(tsh->line, tmp.begin->c, tmp.begin->s_pos,\
					tmp.begin->index);
			tmp.begin = tmp.begin->next;
		}
	}
}

void 		ft_replace_globbling_and_expansion(t_termc *tsh, t_lineterm *end)
{
	dlist 	tmp;
	char 	*word;

	tmp.begin = NULL;
	tmp.end = NULL;
	if (!end->next)
		tsh->line->last = 1;
	else
		tsh->line->last = 0;
	if ((word = ft_get_word(tsh, end)) == NULL)
		return ;
	ft_dupdlnk(tsh->line, &tmp);
	ft_clean_line(tsh);
	ft_split_repl(tsh, tmp, word);
	ft_freedlnk(&tmp);
	free(word);
}
