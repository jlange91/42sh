/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <jlange@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 18:22:31 by jlange            #+#    #+#             */
/*   Updated: 2017/11/28 20:17:45 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/sh21.h"

static int		backslash_word(char *line)
{
	if (line[0] != '\\')
		return (0);
	if (line[1] == '\n')
		return (2);
	else
		return (1);
}

int             type_redir(char *str, int index)
{
    int ret;

    ret = 0;
    if (index > 0 && str[-1] == '\\')
        return (0);
    ret = (str[0] == '>') ? 1 : ret;
    ret = (str[0] == '>' && str[1] == '>') ? 2 : ret;
    ret = (str[0] == '>' && str[1] == '&') ? 3 : ret;
	ret = (str[0] == '<') ? 4 : ret;
	ret = (str[0] == '<' && str[1] == '<') ? 5 : ret;
	if (ret > 0)
		str[0] = ' ';
	if (ret == 2 || ret == 3 || ret == 5)
		str[1] = ' ';
    return (ret);
}

t_redir		*ft_create_redir(int fd, int close)
{
	t_redir	*r;

	r = (t_redir*)malloc(sizeof(t_redir) * 1);
	if (!r)
		return (NULL);
	r->fd = fd;
	r->close = close;
	r->next = NULL;
	return (r);
}

void		ft_add_redir(t_redir **r, int fd, int close)
{
	t_redir *begin;
	t_redir *new;

	begin = *r;
	new = ft_create_redir(fd, close);
	if (!begin)
		*r = new;
	else
	{
		new->next = *r;
		*r = new;
	}
}

int				output_redirection(char *line, int type)
{
	char *word;
	int fd;
	int nb;
	int i;
	
	fd = 0;
	nb = 0;
	i = 0;
	line += ft_skip_useless(line);
	word = ft_ret_word(line, &nb);
	if (type == 1)
		fd = open(word, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(word, O_WRONLY | O_CREAT, 0644);
	lseek(fd, 0, SEEK_END);
	while (i < nb)
	{
		line[i] = ' ';
		++i;
	}
	return (fd);
}

void			ft_redirection(t_shell *sh)
{
	int i;
	int type;

	i = 0;
	type = 0;
	while (sh->line[i])
	{
        i += ft_skip_quote(&sh->line[i]);
		i += ft_skip_dquote(&sh->line[i]);
		type = type_redir(&sh->line[i], i);
		if (type == 1 || type == 2)
		{
			ft_add_redir(&sh->output, output_redirection(&sh->line[i], type), 1);
		}
		if (backslash_word(&sh->line[i]) > 0)
			i++;
		i++;
	}
	if (sh->output)
	{
		sh->output_save = dup(1);
		dup2(sh->output->fd, 1);
	}
}

void test_fd()
{
	for(int i = 3; i < 10000; i++)
	{
		if (close(i)) {
		} else {
			    dprintf(2, "%d, ", i);
				 }
	}
	dprintf(2, "etait ouvert\n");
}

void		ft_remove_redirection(t_shell *sh)
{
	int save;
	t_redir *tmp;

	if (sh->output)
	{
		save = dup(sh->output->fd);
		dup2(sh->output_save, 1);
	}
	test_fd();
	while (sh->output)
	{
		tmp = sh->output;
		sh->output = sh->output->next;
		free(tmp);
	}
}