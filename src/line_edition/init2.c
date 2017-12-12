#include "../../inc/line_edition.h"
#include "../../inc/autocompletion.h"

static	inline	t_console	*init_console(void)
{
	t_console	*console;

	console = NULL;
	if ((console = (t_console *)malloc(sizeof(t_console))) == NULL)
	{
		return (NULL);
	}
	console->total_line = 0;
	console->line_pos = 1;
	console->char_pos = 0;
	return (console);
}

static	inline	hlist		*init_history(void)
{
	hlist	*h;

	h = NULL;
	if ((h = (hlist *)malloc(sizeof(hlist))) == NULL)
	{
		ft_putendl_fd("Error malloc", 2);
		return (NULL);
	}
	h->begin = NULL;
	h->end = NULL;
	h->current = NULL;
	h->active = 0;
    h->ecrase_hist = 0;
    h->down = 0;
    h->up = 0;
    h->line_history = 0;
	return (h);
}

static  inline  t_keyflag   *init_keyflag(void)
{
    t_keyflag   *new;

    if ((new = (t_keyflag *)malloc(sizeof(*new))) == NULL)
    {
        ft_putendl_fd("Error malloc", 2);
        return (NULL);
    }
    new->backspace = 0;
    new->mleft = 0;
    new->mright = 0;
    new->underline = 0;
    new->cl = 0;
    return (new);
}

static	inline	t_auto		*init_autocompletion(void)
{
    t_auto   *autoc;

	autoc = NULL;
	if ((autoc = (t_auto *)malloc(sizeof(t_auto))) == NULL)
	{
		ft_putendl_fd("Error malloc", 2);
		return (NULL);
	}
    autoc->str = NULL;
	autoc->end = NULL;
    autoc->current = NULL;
	autoc->begin = NULL;
    autoc->finish = 0;
    autoc->jump = 0;
    autoc->max_len = 0;
    autoc->row = 0;
    autoc->col = 0;
    autoc->pages = 0;
    autoc->more_pages = 0;
    autoc->nbr_word = 0;
    autoc->updaterow = 0;
    autoc->arrow = 0;
    autoc->clr_yes = 0;
	autoc->can_print = 0;
	autoc->possiblitie = 0;
	return (autoc);
}

static	inline	dlist		*init_lineterm(void)
{
	dlist	*line;

	line = NULL;
	if ((line = (dlist *)malloc(sizeof(dlist))) == NULL)
	{
		ft_putendl_fd("Error malloc", 2);
		return (NULL);
	}
	line->lenght = 0;
	line->lnk_before = 0;
	line->last = 0;
	line->begin = NULL;
	line->end = NULL;
	return (line);
}

void    ft_init_termc2(t_termc **tsh)
{
	if (((*tsh)->line = init_lineterm()) == NULL)
	   ft_putendl_fd("Error init_lineterm", 2);
	if (((*tsh)->line_dup = init_lineterm()) == NULL)
	   ft_putendl_fd("Error init_lineterm", 2);
	if (((*tsh)->history = init_history()) == NULL)
	   ft_putendl_fd("Error init_history", 2);
	if (((*tsh)->from_hist = init_history()) == NULL)
	   ft_putendl_fd("Error init_history", 2);
	if (((*tsh)->console = init_console()) == NULL)
	   ft_putendl_fd("Error init_console", 2);
	if (((*tsh)->autoc = init_autocompletion()) == NULL)
	   ft_putendl_fd("Error init_autocompletion", 2);
	if (((*tsh)->auto_binary = init_autocompletion()) == NULL)
	   ft_putendl_fd("Error init_autocompletion_binary", 2);
	if (((*tsh)->keyflag = init_keyflag()) == NULL)
	   ft_putendl_fd("Error init_keyflag", 2);
}