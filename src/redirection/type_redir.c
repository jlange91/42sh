/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlange <jlange@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 16:30:21 by jlange            #+#    #+#             */
/*   Updated: 2018/01/31 15:05:56 by jlange           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/sh21.h"
#include "../../inc/quote.h"

int				ft_check_fd_in(char *str, int index)
{
	int ret;
	int save;

	ret = -1;
	save = index;
	while (index >= 0 && ft_isdigit(str[index]))
		index--;
	if (index >= 0 && str[index] != ' ' && str[index] != '\t' &&
			str[index] != '\n')
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
			(str[3] == ' ' || str[3] == '\t' || str[3] == '\n' ||
			!str[3])) ? 8 : ret;
	str[0] = ' ';
	if (ret > 2)
		str[1] = ' ';
	if (ret == 8)
		str[2] = ' ';
	return (ret);
}

int				directory_fd(char *line, int type)
{
	char	*word;
	int		fd;
	int		i;

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
		fd = open(ft_var_hrdcpwd(NULL), O_RDWR | O_CREAT | O_TRUNC, 0644);
	else if (type == 7)
		fd = open(word, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd != -1 && type == 4)
		lseek(fd, 0, SEEK_END);
	if (fd == -1)
		ft_perror("shell", errno, word);
	if (word)
		free(word);
	return (fd);
}

t_redir			*type_redir(char *str, int index, int len, int i)
{
	t_redir	*red;

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
		while (++i < len)
			str[i + 2] = ' ';
	}
	red->type = ft_check_type_redir(str);
	if (red->type != 8 && red->out == -1)
		red->out = directory_fd(str, red->type);
	return (red);
}
