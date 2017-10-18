#include "../../inc/built_in.h"

int 	ft_dquote(char *str)
{
	size_t	i;
	int		count;

	i = 0;
	count = 0;
		while (i < ft_strlen(str))
		{
			if (str[i] == '"')
				count++;
			i++;
		}
	return (count %2 != 0);
}

int 	ft_quote(char *str)
{
	size_t	i;
	int		count;

	i = 0;
	count = 0;
	while (i < ft_strlen(str))
	{
		if (str[i] == '\'')
			count++;
		i++;
	}
	return (count %2 != 0);
}

void 	ft_dodquote(t_env **env)
{
	char 	buffer[5];
	char 	*temp;
	t_env	*ev;

	temp = "\n";
	ev = *env;
	ft_putstr("\ndquote> ");
	while (1)
	{
		ft_bzero(buffer, 5);
		read(0, buffer, 4);
		ft_putstr(buffer);
		if (ft_strcmp(buffer, "\n") == 0 && !ft_dquote(temp))
			ft_putstr("dquote> ");
		temp = ft_strjoin(temp, buffer);
		if (ft_strcmp(buffer, "\n") == 0 && ft_dquote(temp))
			break;
	}
	temp = ft_strtrim_c(temp, '"');
	ev->line_str = ft_strjoin(ft_strtrim_c(ev->line_str, '"'), temp);
}

void 	ft_doquote(t_env **env)
{
	char 	buffer[5];
	char 	*temp;
	t_env	*nv;

	temp = "\n";
	nv = *env;
	ft_putstr("\nquote> ");
	while (1)
	{
		ft_bzero(buffer, 5);
		read(0, buffer, 4);
		ft_putstr(buffer);
		if (ft_strcmp(buffer, "\n") == 0 && !ft_quote(temp))
			ft_putstr("quote> ");
		temp = ft_strjoin(temp, buffer);
		if (ft_strcmp(buffer, "\n") == 0 && ft_quote(temp))
			break;
	}
	temp = ft_strtrim_c(temp, '\'');
	nv->line_str = ft_strjoin(ft_strtrim_c(nv->line_str, '\''), temp);
}
