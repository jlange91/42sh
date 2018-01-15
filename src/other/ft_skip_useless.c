int		ft_skip_useless(char *line)
{
	int i;

    i = 0;
    while (line[i])
    {
        if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
            break ;
	    while (line[i] == ' ' || line[i] == '\t' || line[i] == '\n')
            i++;
    }
	return (i);
}