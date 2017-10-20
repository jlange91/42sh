int     ft_char_escape(char c)
{
    if (c == '\'' || c == '"' || c == '`' || c == '\\')
        return (1);
    else
        return (0);
}