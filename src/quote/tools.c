int     ft_char_escape(char c)
{
    if (c == '\'' || c == '"' || c == '`' || c == '\\')
        return (1);
    else
        return (0);
}

void    ft_charcat(char *str, char c)
{
	int i;

    i = 0;
	while (str[i])
        i++;
    str[i] = c;
    str[i + 1] = '\0';
}
