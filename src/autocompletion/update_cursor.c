#include "../../inc/autocompletion.h"

static inline int ft_gnl(const int fd)
{
	unsigned char   buffer[4];
	ssize_t         n;

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
}

static int ft_write_to(const int fd, const char *const data, const size_t bytes)
{
	const char       *head = data;
	const char *const tail = data + bytes;
	ssize_t           n;

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

static int ft_parse_cursor(int val, int result, int tty)
{
	int rows;

	rows = 0;
	while (val)
	{
		val = ft_write_to(tty, "\033[6n", 4);
		if ((result = ft_gnl(tty)) != 27
				|| (result = ft_gnl(tty)) != '[')
			break;
		result = ft_gnl(tty);
		while (result >= '0' && result <= '9')
		{
			rows = 10 * rows + result - '0';
			result = ft_gnl(tty);
		}
		if (result != ';')
			break;
		result = ft_gnl(tty);
		while (result >= '0' && result <= '9')
			result = ft_gnl(tty);
		if (result != 'R')
			break;
		val = 0;
	}
	return (rows);
}

int ft_current_tty(void)
{
	const char *dev;
	int         fd;

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

int ft_cursor_position(const int tty, int *const rowptr)
{
	struct termios  saved;
	struct termios  temporary;
	int             val;
	int             result;

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
