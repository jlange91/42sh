#include "../../inc/sh21.h"

void		ft_remove_redirection()
{
	dup2(ft_backup_stdin(0), 0);
	close(ft_backup_stdin(0));
	dup2(ft_backup_stdout(0), 1);
	close(ft_backup_stdout(0));
	dup2(ft_backup_stderr(0), 2);
	close(ft_backup_stderr(0));
}