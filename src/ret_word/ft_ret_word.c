#include "../../inc/sh21.h"

char    *ft_ret_word(char *line, int *size)
{
    char *word;

    word = (char*)malloc(sizeof(char) * (ft_count_char_word(line, size) + 1));
    word[0] = '\0';
    ft_fill_word(line, word);
    return (word);
}