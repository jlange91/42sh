# include "../inc/sh21.h"
# include "../inc/quote.h"

static int		backslash_word(char *line)
{
	if (line[0] != '\\')
		return (0);
	if (line[1] == '\n')
		return (2);
	else
		return (1);
}

t_cmd	*ft_create_cmd(char *line, int op)
{
	t_cmd		*ret;
	static int	top = 0;

	ret = (t_cmd*)malloc(sizeof(t_cmd) * 1);
	if (!ret)
	{
		ft_perror("malloc", errno, NULL);
		exit(0);
	}
	ret->line = ft_strdup(line);
	ret->av = ft_fill_av(line);
	ret->ac = tab_2d_len(ret->av);
	ret->hrdc = NULL;
	ret->r_op = op;
	ret->l_op = 0;
	ret->next = NULL;
	top = op;
	return (ret);
}

void	ft_add_cmd(t_cmd **begin, char *line, int op)
{
	t_cmd *cmd;
	t_cmd *new;

	cmd = *begin;
	new = ft_create_cmd(line, op);
	if (!cmd)
		*begin = new;
	else
	{
		while (cmd->next)
			cmd = cmd->next;
		cmd->next = new;
		new->l_op = cmd->r_op;
	}
}

int     is_end(char *line)
{
	int ret;

	ret = 0;
	ret = (line[0] == 0 || line[0] == '\n') ? 1 : ret;
	ret = (line[0] == ';') ? 2 : ret;
	ret = (line[0] == '&' && line[1] == '&') ? 3 : ret;
	ret = (line[0] == '|') ? 5 : ret;
	ret = (ret == 5 && line[1] == '|') ? 4 : ret;
	return (ret);
}

t_cmd	*ft_fill_cmd(char *line, int i, int j)
{
	t_cmd	*cmd;
	char    *cline;
	int     op;

	cmd = NULL;
	while (42)
	{
		i += ft_skip_quote(&line[i]);
		i += ft_skip_dquote(&line[i]);
		if ((op = is_end(&line[i])))
		{            
			cline = ft_strndup(&line[j], i - j);
			ft_add_cmd(&cmd, cline, op - 1);
			free(cline);
			j = (op == 3 || op == 4) ? i + 2 : i + 1;
			i += (op == 3 || op == 4) ? 1 : 0;
			if (op == 1)
				return (cmd);
		}
		if (backslash_word(&line[i]) > 0)
			i++;
		i++;
	}
	return (cmd);
}
