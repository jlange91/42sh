int		ft_intlen(int nb)
{
	int ret;

	ret = 1;
	while (nb / 10)
	{
		nb = nb / 10;
		ret++;
	}
	return (ret);
}