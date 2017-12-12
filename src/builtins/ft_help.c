#include "../../inc/sh21.h"

void	ft_help(t_shell *sh)
{
	char	**arg;
	char	*str;
	pid_t	father;
	
	str = "COPIER/COLLER COUPER/COLLER SE_DEPLACER SELECTION AUTOCOMPLETION GLOBBING HISTORIQUE";
	arg = ft_strsplit(str, ' ');

	father = fork();
	if (father == 0)
		execve("/tmp/./builtin_help", arg, sh->env);
	else
		wait(0);
}
