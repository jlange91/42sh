int				ft_skip_dquote(char *str)
{
	int i;

	i = 1;
	if (str[0] == '"')
	{
		while (str[i] != '"')
			i++;
		return (i);
	}
	else
		return (0);
}