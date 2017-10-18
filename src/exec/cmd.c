#include "../../inc/exec.h"
#include "../../inc/env_term.h"
#include "../../inc/line_edition.h"

static	char	*ft_path_try(char *av, char *dir)
{
	char	*path;
	int		len_max;

	len_max = ((ft_strlen(av) + 1) + (ft_strlen(dir) + 1));
	if ((path = (char *)malloc(sizeof(*path) * len_max)) == NULL)
		return (NULL);
	ft_strcpy(path, dir);
	ft_strcat(path, "/");
	ft_strcat(path, av);
	if (access(path, X_OK) == 0)
		return (path);
	free(path);
	path = NULL;
	return (path);
}

static	char	*ft_path(char *str, t_env *env)
{
	char *path;
    char *tmp;
    char **dtab;
    int  i;

	path = NULL;
    dtab = NULL;
    tmp = NULL;
	path = ft_getenv("PATH", env);
	if (path != NULL)
	{
		i = -1;
        dtab = ft_strsplit(path, ':');
		while (dtab[++i])
			if ((tmp = ft_path_try(str, dtab[i])) != NULL)
			{
	            ft_free_tab(dtab);
				return (tmp);
			}
	}
	return (str);
}

int    ft_cmd_exe(char *str, t_cmd *cmd, t_env *env)
{
    char    **env_tab;
    char    **argv;
    pid_t   pid;
    int     fd;
    int     save;

    signal(SIGINT, ft_handle_signal2);
    pid = fork();
    env_tab = ft_env_to_tab(env);
    argv = ft_cmd_to_tab(cmd);
    if (pid > 0)
        waitpid(pid, NULL, 0);
    if (pid == 0)
    {
        save = dup(1);
        tputs(tgetstr("do", NULL), 1, ft_inputstr);
        if (cmd->type == TOKEN_R_R)
        {
            if (ft_strcmp(cmd->str_type, ">") == 0)
            {
                ft_putendl_fd("Error syntax", 2);
                return (0);
            }
            fd = open(cmd->str_type, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR 
                    | S_IWUSR | S_IRGRP | S_IROTH);
            if (fd == -1)
                ft_putendl_fd("Error fd", 2);
            else
            {
                if (dup2(fd, 1) < 0)
                    ft_putendl_fd("Error dup2", 2);
                close(fd);
            }
        }
        if ((execve(ft_path(str, env), argv, env_tab)) == -1)
        {
            dup2(save, 1);
            close(save);
            ft_putstr_fd("42sh: ", 2);
            ft_putstr_fd(str, 2);
            ft_putchar(':');
            ft_putstr_fd(" command no found", 2);
            ft_free_all_cmd(argv, env_tab);
			return (0);
        }
    }
    ft_free_all_cmd(argv, env_tab);
    return (1);
}
/*int    ft_cmd_exe(char *str, t_cmd *cmd, t_env *env)
{
    char    **env_tab;
    char    **argv;
    pid_t   pid;

    signal(SIGINT, ft_handle_signal2);
    pid = fork();
    env_tab = ft_env_to_tab(env);
    argv = ft_cmd_to_tab(cmd);
    if (pid > 0)
        waitpid(pid, NULL, 0);
    if (pid == 0)
    {
        tputs(tgetstr("do", NULL), 1, ft_inputstr);
        if ((execve(ft_path(str, env), argv, env_tab)) == -1)
        {
            ft_putstr_fd("42sh: ", 2);
            ft_putstr_fd(str, 2);
            ft_putendl_fd(": command no found", 2);
            ft_free_all_cmd(argv, env_tab);
            exit(0);
        }
    }
    ft_free_all_cmd(argv, env_tab);
    return (1);
}*/
