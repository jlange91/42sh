/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stvalett <stvalett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 19:23:56 by stvalett          #+#    #+#             */
/*   Updated: 2017/11/17 10:02:15 by stvalett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../inc/line_edition.h"
#include "../../inc/autocompletion.h"
#include "../../inc/globbing.h"

t_termc *shell_g = NULL;
char **g_env = NULL;

/************************************************************************************
 * FUNCTION GETSTR 
 * ALL VARIABLE				nbr ==> for good malloc
 *	
 *	EXPLICATION : this function transform double linked to string
 *
 * NO NORME
 ***********************************************************************************/ 

static inline char  *ft_getstr(t_termc *shell, t_lineterm *begin, int nbr)
{
	t_lineterm *tmp;
	char        *str;
	int         i;

	tmp = begin;
	i = 0;
	str = NULL;
	if (!tmp)
		return (NULL);
	else if (tmp->next)
		tmp = ft_dont_get_prompt(tmp);
	str = (shell->history->active == 1) ? 
		(char *)malloc(sizeof(char) * ft_count_dlnk(shell) + 1) :
		(char *)malloc(sizeof(char) * nbr + 1);
	if (!str)
		return (NULL);
	while (tmp)
	{
		if (i == 0 && tmp->c == ' ')
			tmp = tmp->next;		
		str[i++] = tmp->c;
		tmp = tmp->next;
	}
	str[i] = '\0';
	if (ft_strlen(str) >= 1)
		ft_add_tmp_history(shell, str);
	return (str);
}

static int    ft_key_and_char(t_termc *shell, long c, char **env)
{
	if (c == CL && !shell->auto_active && !shell->multiauto_active)
	{
		t_lineterm *tmp;

		tputs(shell->term->clrstr, 1, ft_inputstr);
		ft_display(shell, 0, 1);
		shell->keyflag->cl = 1;
		tmp = shell->line->begin;
		tmp = ft_dont_get_prompt(tmp);
		if (shell->line_dup->begin)
			ft_free_dlist(&shell->line_dup);
		while (tmp)
		{
			ft_fill_back_dlst(shell->line_dup, tmp->c, 1);
			tmp = tmp->next;
		}
		return (0);
	}
	if ((ft_is_key(shell->line, shell, c, env) == 0 && ft_isprint((char)c)))
	{
		shell->auto_active = 0;
		shell->multiauto_active = 0;
		shell->count_tab = 0;
		if (shell->line->lnk_before)
			ft_insert_dlnk(shell->line->end, shell, c, 1);
		else
			ft_fill_back_dlst(shell->line, c, 1);
		if (ft_isprint((char)c) && c != BACKSPACE && c
				!= LEFT && c != RIGHT && c != UP && c != DOWN)
			ft_find_history(shell);
	}
	else
		shell->line->lnk_before = 1;
	if (shell->line->last)
		shell->line->lnk_before = 0;
	return (1);
}

/************************************************************************************
 * FUNCTION CATCH KEY 
 * ALL VARIABLE				ret ==> how time cursor jump, adjust cursor
 *                          FIRST CONDITION : IF C is ENTER, STOP AND RETURN FOR CHECK LINE        
 *                          SECOND CONDITION : JUMP 2 LINES FOR GOOD DISPLAY
 *                          THIRD CONDITION : CHECK IS ARROWS OR ADD CARACTERE PRINTABLE
 * NO NORME
 * **********************************************************************************/
static int  ft_key_or_escape(long c, t_termc *shell, int ret, char **env)
{ 
	if ((char)c == '\n' && !shell->count_tab)
		return (ft_reset_line(shell, ret));
	if ((shell->auto_active == 1 || shell->multiauto_active == 1)
			&& (c == LEFT || c == RIGHT ||
				c == DOWN || c == UP || c == TAB))
	{
		tputs(shell->term->upstr, 1, ft_inputstr);
		tputs(shell->term->upstr, 1, ft_inputstr);
	}
	if (!ft_key_and_char(shell, c, env))
		return (0);
	return (1);
}

static void	ft_line_input_split(t_termc *tsh, int *nbr, int *ret, char **env)
{
	*nbr = 0;
	*ret = 0;
	tsh->history->active = 0;
	tsh->line->lnk_before = 0;
	tsh->autocompl->jump = 0;
	tsh->quotes = 0;
	ft_init_console(tsh, tsh->line);
	ft_init_simple_autocompl(tsh, env);
	ft_display_char(tsh->line->begin, tsh);
}

/************************************************************************************
 * FUNCTION HEART
 * ALL VARIABLE				ret ===> how time cursor jump
 * 							nbr ===> total number from line, for good malloc
 * 							in function ft_getstr
 *
 * 	Explication : read input caractere and check if is key or cactere and display
 *
 * 	NO NORME
 * 	*********************************************************************************/
char    *ft_line_input(t_termc *shell, char **env)
{
	long 	c;
	int 	nbr;
	int 	ret;
	//char	*tmp;

	if (isatty(0))
	{
		shell_g = shell;
		g_env = env;
		c = 0;
		ft_line_input_split(shell, &nbr, &ret, env);
		if (shell->keyflag->cl)
		{
			t_lineterm *tmp;

			tmp = shell->line_dup->begin;
			while (tmp)
			{
				ft_fill_back_dlst(shell->line, tmp->c, 1);
				tmp = tmp->next;
			}
			ft_display(shell, &nbr, 0);
		}
		while (read(0, &c, sizeof(c)))
		{
			if (!ft_key_or_escape(c, shell, ret, env))
				break;
			ret = ft_display(shell, &nbr, 0);
			shell_g->ret_signal = ret;
			c = 0;
			shell->keyflag->backspace = 0;
			shell->keyflag->underline = 0;
			shell->keyflag->mleft = 0;
		}
		/*tmp = ft_to_str(shell);
		if (ft_can_replace_glob(tmp) == 1)
			ft_replace_glob(shell, tmp, env);			//MUST CHANGE ENV
		free(tmp);*/
		return (ft_getstr(shell, shell->line->begin, nbr));
	}
	return (NULL);
}
