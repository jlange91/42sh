#include "../../inc/line_edition.h"
#include "../../inc/autocompletion.h"
#include "../../inc/globbing.h"
#include "../../inc/sh21.h"

// static inline char *ft_hist_to_repl(char *word, int flag, hlist *hist)
// {
// 	int 	i;
// 	int 	ret;
// 	char 	*tmp;
// 	t_history *end;
//
// 	end = hist->end;
// 	if (!flag || flag == 1)
// 	{
// 		i = 0;
// 		while (word[i] && ft_isdigit(word[i]))
// 			i++;
// 		tmp = ft_strndup(word, i);
// 		ret = ft_atoi(tmp);
// 		free(tmp);
// 	}
// 	if (flag == 2)
// 	{
// 		i = 0;
// 		while (word[i])
// 		{
// 			if (word[i] == ' ')
// 				break ;
// 			i++;
// 		}
// 		tmp = ft_strndup(word, i);
// 	}
// 	while (end)
// 	{
// 		if (!flag && ret-- == 1)
// 			return (end->data);
// 		else if (flag && ret == end->index)
// 			return (end->data);
// 		else if (flag == 2 && !ft_strncmp(tmp, end->data, ft_strlen(tmp)))
// 			return (end->data);
// 		end = end->prev;
// 	}
// 	if (flag == 2)
// 		free(tmp);
// 	return (NULL);
// }

static inline void ft_cpy(char *line, t_termc *tsh)
{
	int i;

	i = 0;
	// tsh->autoc->updaterow = 0;
	while (line[i])
	{
		push_backdlst(tsh->line, line[i], 1);
		i++;
	}
}

static inline int 	ft_find_prev(char *word, int i, t_termc *tsh)
{
	int 		ret;
	char 		*tmp;
	t_history 	*end;

	if (word[i] == '!')
		ft_cpy(tsh->histlist->end->data, tsh);
	else if (word[i] == '-')
	{
		end = tsh->histlist->end;
		ret = 0;
		if (!ft_isdigit(word[i + 1]))
			tmp = ft_strdup(&word[i - 1]);
		if ((ret = ft_atoi(tmp)))
		{
			while (end)
			{
				if (ret-- == 1)
					break ;
				end = end->prev;
			}
			ft_cpy(end->data, tsh);
		}
		else
			ft_cpy(tmp, tsh);
		free(tmp);
	}
	return (++i);
}

static inline int 	ft_replace_pattern(char *word, int i, t_termc *tsh)
{
	if (word[i] == '!' || word[i] == '-')
			return (ft_find_prev(word, i, tsh));
	else
		push_backdlst(tsh->line, word[i - 1], 1);
	return (i);
}

void 			ft_replace_exp_hist(t_termc *tsh)
{
	char		*line;
	int 		i;

	if ((line = ft_to_str(tsh)) != NULL)
	{
		ft_clean_line(tsh);
		i = 0;
		while (line[i])
		{
			if (line[i] == '!')
				i = ft_replace_pattern(line, ++i, tsh);
			else
			{
				push_backdlst(tsh->line, line[i], 1);
				i++;
			}
		}
		free (line);
	}
}
