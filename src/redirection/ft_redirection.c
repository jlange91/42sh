/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirrection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <jlange@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 18:22:31 by jlange            #+#    #+#             */
/*   Updated: 2017/12/12 14:54:08 by jlange           ###   ########.fr       */
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

int				ft_check_fd_in(char *str, int index)
{
	int ret;
	int save;

	ret = -1;
	save = index;
	while (index >= 0 && ft_isdigit(str[index]))
		index--;
	if (index >= 0 && str[index] != ' ' && str[index] != '\t' && str[index] != '\n')
		return (ret);
	ret = (save != index) ? ft_atoi(&str[index + 1]) : ret;
	while (index != save)
	{
		++index;
		str[index] = ' ';
	}
	return (ret);
}

int				ft_check_type_redir(char *str)
{
	int ret;

	ret = 0;
	ret = (str[0] == '>') ? 1 : ret;
	ret = (str[0] == '<') ? 2 : ret;
	ret = (str[0] == '>' && str[1] == '&') ? 3 : ret;
    ret = (str[0] == '>' && str[1] == '>') ? 4 : ret;
	ret = (str[0] == '<' && str[1] == '&') ? 5 : ret;
	ret = (str[0] == '<' && str[1] == '<') ? 6 : ret;
	ret = (str[0] == '<' && str[1] == '>') ? 7 : ret;
	ret = (str[0] == '>' && str[1] == '&' && str[2] == '-' &&
	(str[3] == ' ' || str[3] == '\t' || str[3] == '\n' || str[3] == '\0')) ? 8 : ret;
	str[0] = ' ';
	if (ret > 2)
		str[1] = ' ';
	if (ret == 8)
		str[2] = ' ';
	return (ret);
}

int		ft_intlen(int	nb)
{
	int ret;

	ret = 1;
	while (nb / 10)
	{
		nb = nb / 10;
		ret++;
	}
	return (ret);
}

int				directory_fd(char *line, int type)
{
	char *word;
	int fd;
	int i;

	fd = 0;
	i = 0;	
	line += ft_skip_useless(line);	
	word = ft_ret_word(line);
	if (type == 1 || type == 3)
		fd = open(word, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == 2 || type == 5)
		fd = open(word, O_RDONLY | O_CREAT, 0644);
	else if (type == 4)
		fd = open(word, O_WRONLY | O_CREAT, 0644);
	else if (type == 6)
		fd = open("/tmp/.heardocs_42sh", O_RDWR | O_CREAT | O_TRUNC, 0644);
	else if (type == 7)
		fd = open(word, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd != -1 && type == 4)
		lseek(fd, 0, SEEK_END);
	if (fd == -1)
		ft_perror("42sh", errno, word);
	return (fd);
}

t_redir             *type_redir(char *str, int index)
{
	t_redir	*red;
	int		len;
	int		i;

	len = 0;
	i = 0;
	if (!(red = (t_redir*)malloc(sizeof(t_redir) * 1)))
	{
		ft_perror("malloc", errno, NULL);
		exit(0);
	}
	red->in = ft_check_fd_in(&str[-index], index - 1);
	red->out = (str[1] == '&' && ft_isdigit(str[2])) ? ft_atoi(&str[2]) : -1;
	red->close = (red->out == -1) ? 1 : 0;
	if (red->out >= 0)
	{
		len = ft_intlen(red->out);
		while (i < len)
		{
			str[i + 2] = ' ';
			i++;
		}
	}
	red->type = ft_check_type_redir(str);
	if (red->type != 8 && red->out == -1)
		red->out = directory_fd(str, red->type);
	//printf("in : {%d} out {%d} type: {%d}\nstr : {%s}\n", red->in, red->out, red->type, &str[-index]);
	return (red);
}

int			ft_backup_stdin(int nb)
{
	static int stdout = 0;

	if (nb == 1)
		stdout = dup2(0, 100);
	return (stdout);
}

int			ft_backup_stdout(int nb)
{
	static int stdout = 0;

	if (nb == 1)
		stdout = dup2(1, 101);
	return (stdout);
}

int			ft_backup_stderr(int nb)
{
	static int stdout = 0;

	if (nb == 1)
		stdout = dup2(2, 102);
	return (stdout);
}

void		ft_redirr_type8(t_redir *red)
{
	if (red->in == -1)
		close(1);
	else if (red->in != ft_backup_stdin(0) &&
		red->in != ft_backup_stdout(0) &&
		red->in != ft_backup_stderr(0))
		close(red->in);
}

int			ft_redirr_type1(t_redir *red)
{
	return (dup2(red->out , (red->in == -1) ? 1 : red->in));
}

int			ft_redirr_type2(t_redir *red)
{
	return (dup2(red->out , (red->in == -1) ? 0 : red->in));
}

int			ft_diff_backup(int nb)
{
	return (nb == ft_backup_stdin(0) || nb == ft_backup_stdout(0) || nb == ft_backup_stderr(0)) ? 1 : 0;
}

t_toclose	*ft_create_close_fd(int fd)
{
	t_toclose *ret;

	if ((ret = (t_toclose*)malloc(sizeof(t_toclose) * 1)) == NULL)
	{
		ft_perror("malloc", errno, NULL);
		exit(0);
	}
	ret->fd = fd;
	ret->next = NULL;
	return (ret);
}

void		ft_add_close_fd(t_toclose **cfd, int fd)
{
	t_toclose *new;
	t_toclose *begin;

	begin = *cfd;
	new = ft_create_close_fd(fd);
	if (!begin)
	{
		*cfd = new;
		return ;
	}
	while (begin->next)
		begin = begin->next;
	begin->next = new;
}

int			ft_redirection(t_shell *sh)
{
	int i;
	t_redir *red;

	i = 0;
	ft_backup_stdin(1);
	ft_backup_stdout(1);
	ft_backup_stderr(1);
	while (sh->line[i])
	{
        i += ft_skip_quote(&sh->line[i]);
		i += ft_skip_dquote(&sh->line[i]);
		if ((sh->line[i] == '>' || sh->line[i] == '<') && !(i > 0 && sh->line[i - 1] == '\\'))
		{
			red = type_redir(&sh->line[i], i);
			if (red->out == -1)
			{
				free(red);
				return (-1);
			}
			if (red->in != -1)
				ft_add_close_fd(&sh->cfd, red->in);
			if (red->type == 8)
				ft_redirr_type8(red);
			else if (red->type == 1 || red->type == 4 || red->type == 3 || red->type == 7)
			{
				if (ft_diff_backup(red->out) || ft_redirr_type1(red) == -1)
				{
					ft_perror("42sh", errno, NULL);
					return (-1);
				}
			}
			else if (red->type == 2 || red->type == 5)
			{
				if (ft_diff_backup(red->out) || ft_redirr_type2(red) == -1)
				{
					ft_perror("42sh", errno, NULL);
					return (-1);
				}
			}
			if (red->close)
				close(red->out);
			free(red);
		}
		if (backslash_word(&sh->line[i]) > 0)
			i++;
		i++;
	}
	return (0);
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
	t_toclose *tmp;

	sh = (void*)sh;
	while (sh->cfd)
	{
		tmp = sh->cfd;
		sh->cfd = sh->cfd->next;
		close(tmp->fd);
		free(tmp);
	}
	dup2(ft_backup_stdin(0), 0);
	close(ft_backup_stdin(0));
	dup2(ft_backup_stdout(0), 1);
	close(ft_backup_stdout(0));
	dup2(ft_backup_stderr(0), 2);
	close(ft_backup_stderr(0));
	test_fd();
}