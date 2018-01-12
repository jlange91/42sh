#include "../../inc/line_edition.h"
#include "../../inc/sh21.h"

void	ft_init_termc3(t_termc *tsh)
{
	tsh->color = NULL;
	if (!(tsh->color = (char **)malloc(sizeof(char*) * 7 )))
		return ;
	tsh->color[0] = RED;
	tsh->color[1] = BLUE;
	tsh->color[2] = YELLOW;
	tsh->color[3] = PINK;
	tsh->color[4] = GREEN;
	tsh->color[5] = RESET;
	tsh->color[6] = NULL;
	tsh->path = 0;
	tsh->prompt = 1;
	tsh->host = 2;
	tsh->hour = 3;
	tsh->linep = 4;
}
