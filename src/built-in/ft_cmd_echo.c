#include "../../inc/built_in.h"
#include "../../inc/sh21.h"

char	*find_in_env(t_env *env, char *search)
{
	char *str;

	if (search == 0 || ft_strcmp(search, "") == 0)
		return (0);
	while (env)
	{
		str = ft_strbchr(env->line_env, '=');
		if (ft_strcmp(str, search) == 0)
		{
			ft_strdel(&str);
			return (ft_strchr(env->line_env, '=') + 1);
		}
		ft_strdel(&str);
		env = env->next;
	}
	return (str);
}

void	ft_cmd_echo(t_cmd *cmd, t_env *env)
{
	char *temp;
	char **tab;
	int i;

	(void)cmd;
	temp = env->line_str;
	tab = ft_strsplit(temp, ' ');
	i = 1;
	if (ft_count_dtab(tab) > 1)
	{
		ft_putchar('\n');
		while(tab[i])
		{
			if(tab[i][0] == '$')
			{
				if (find_in_env(env, tab[i] + 1))
					ft_putstr(find_in_env(env, tab[i] + 1));
				else
					ft_putstr(tab[i]);
			}
			else
			{
				temp = ft_escapequote(tab[i]);
				ft_putstr(temp);
				ft_strdel(&temp);
			}
			ft_putchar(' ');
			i++;
		}
	}
}
