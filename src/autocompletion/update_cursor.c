/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_cursor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmartins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 19:14:20 by vmartins          #+#    #+#             */
/*   Updated: 2018/01/23 17:26:26 by vmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/autocompletion.h"

/*
**@function
**@param
**@return
*/

static	inline	int	ft_gnl(const int fd)
{
	unsigned char	buffer[4];
	ssize_t			n;

	while (1)
	{
		n = read(fd, buffer, 1);
		if (n > (ssize_t)0)
			return (buffer[0]);
		else if (n == (ssize_t)0)
			return (RD_EOF);
		else if (n != (ssize_t)-1)
			return (RD_EIO);
	}
	return (0);
}

/*
**@function
**@param
**@return
*/

static	int			ft_wrt(const int fd, const char *data, const size_t bytes)
{
	char			*head;
	char			*tail;
	ssize_t			n;

	head = (char *)data;
	tail = (char *)data + bytes;
	while (head < tail)
	{
		n = write(fd, head, (tail - head));
		if (n > (ssize_t)0)
			head += n;
		else if (n != (ssize_t)-1)
			return (RD_EIO);
	}
	return (0);
}

/*
**@function
**@param
**@return
*/

static	int			ft_parse_cursor(int val, int result, int tty)
{
	int				rows;

	rows = 0;
	while (val)
	{
		val = ft_wrt(tty, "\033[6n", 4);
		if ((result = ft_gnl(tty)) != 27
				|| (result = ft_gnl(tty)) != '[')
			break ;
		result = ft_gnl(tty);
		while (result >= '0' && result <= '9')
		{
			rows = 10 * rows + result - '0';
			result = ft_gnl(tty);
		}
		if (result != ';')
			break ;
		result = ft_gnl(tty);
		while (result >= '0' && result <= '9')
			result = ft_gnl(tty);
		if (result != 'R')
			break ;
		val = 0;
	}
	return (rows);
}

/*
**@function Ask ttyname of term and get fd of term
**@param
**@return	good fd or -1 if is bad
*/

int					ft_current_tty(void)
{
	const char		*dev;
	int				fd;

	dev = ttyname(0);
	if (!dev)
		dev = ttyname(1);
	if (!dev)
		dev = ttyname(2);
	if (!dev)
		return (-1);
	fd = open(dev, O_RDWR | O_NOCTTY);
	if (fd == -1)
		return (-1);
	return (fd);
}

/*
**@function	Init TERMINAL MODE, GET CURSOR POS
**@param	1 = tty name termnial
**			2 = Pointeur to get result
**@return
*/

int					ft_cursor_position(const int tty, int *const rowptr)
{
	struct termios	saved;
	struct termios	temporary;
	int				val;
	int				result;

	if ((result = tcgetattr(tty, &saved)) == -1)
		return (-1);
	if ((result = tcgetattr(tty, &temporary)) == -1)
		return (-1);
	temporary.c_lflag &= ~ICANON;
	temporary.c_lflag &= ~ECHO;
	temporary.c_cflag &= ~CREAD;
	result = tcsetattr(tty, TCSANOW, &temporary);
	val = 1;
	*rowptr = ft_parse_cursor(val, result, tty);
	result = tcsetattr(tty, TCSANOW, &saved);
	return (0);
}
