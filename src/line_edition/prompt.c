#include "../../inc/line_edition.h"
#include "../../inc/built_in.h"

static	void	ft_print_hour(void)
{
	time_t		time_sec;
	struct tm	now;
    char        *tmp;

	time(&time_sec);
	now = *localtime(&time_sec);
	ft_putstr(" [");
    tmp = ft_itoa(now.tm_hour);
    if (ft_strlen(tmp) == 1)
        ft_putchar('0');
    free(tmp);
	ft_putnbr(now.tm_hour);
	ft_putchar(':');
    tmp = ft_itoa(now.tm_min);
    if (ft_strlen(tmp) == 1)
        ft_putchar('0');
    free(tmp);
	ft_putnbr(now.tm_min);
	ft_putchar(':');
    tmp = ft_itoa(now.tm_sec);
    if (ft_strlen(tmp) == 1)
        ft_putchar('0');
    free(tmp);
	ft_putnbr(now.tm_sec);
	ft_putstr("] ");
}

static	int	ft_print_current_work()
{
	t_shell *sh;

	sh = ft_ret_sh(NULL);
    ft_putstr(GREEN_FRONT);
	ft_putendl(sh->pwd);
	ft_putstr(RESET);
	return (ft_strlen(sh->pwd));
}

void			ft_display_prompt(t_termc *tsh)
{
	int			len;
	char		host[256];

	len = 10;
	gethostname(host, sizeof(host));
	len += ft_strlen(host);
	ft_putendl("");
	ft_putstr(YELLOW);
	if (ft_singleton(0,0))
		ft_putstr("😡");
	else
		ft_putstr("😃");
	ft_print_hour();
	ft_putstr(RESET);
	ft_putstr(PINK);
	ft_putstr(host);
	ft_putstr(RESET);
	ft_putchar(' ');
	len += ft_print_current_work();
	tsh->len_prompt = len + 3;
}
