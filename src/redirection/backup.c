#include <unistd.h>

int			ft_backup_stdin(int nb)
{
	static int stdout = 0;

	if (nb == 1)
		stdout = dup(0);
	return (stdout);
}

int			ft_backup_stdout(int nb)
{
	static int stdout = 0;

	if (nb == 1)
		stdout = dup(1);
	return (stdout);
}

int			ft_backup_stderr(int nb)
{
	static int stdout = 0;

	if (nb == 1)
		stdout = dup(2);
	return (stdout);
}