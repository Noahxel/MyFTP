/*
** EPITECH PROJECT, 2022
** minishell1
** File description:
** my_str_to_word_array
*/

#include "../includes/my_ftp.h"
#include <stdlib.h>
#include <stdio.h>

int my_strlen(char *str)
{
    int i = 0;

    while (str[i] != '\0')
        i++;
    return (i);
}

char **my_fill_array(char *str, char **word_array, char separator)
{
    int x = 0;
    int j = 0;
    int start = 0;

    for (; str[start] == separator; start++);
    for (int i = start; i <= my_strlen(str); i++) {
        if ((str[i] == separator && str[i + 1] != separator) ||
            (str[i] == '\0')) {
            word_array[j][x] = '\0';
            j++;
            x = 0;
            continue;
        }
        if (str[i] != separator) {
            word_array[j][x] = str[i];
            x++;
        }
    }
    word_array[j] = NULL;
    return (word_array);
}

char **malloc_it(char **word_array, char *str, char separator)
{
    int word_counter = 0;
    int letter_counter = 0;
    int start = 0;

    for (; str[start] == separator; start++);
    for (int i = start; i <= my_strlen(str); i++) {
        if ((str[i] == separator && str[i + 1] != separator) ||
            (str[i] == '\0')) {
            word_array[word_counter] =
                malloc(sizeof(char) * (letter_counter + 1));
            word_counter++;
            letter_counter = 0;
        } else
            letter_counter++;
    }
    return (word_array);
}

char **my_str_to_word_array(char *str, char separator)
{
    int count_word = 0;
    int start = 0;
    char **word_array = NULL;

    for (; str[start] == separator; start++);
    for (int i = start; i <= my_strlen(str); i++) {
        if ((str[i] == separator && (str[i + 1] != separator)) ||
            (str[i] == '\0'))
            count_word++;
    }
    word_array = malloc(sizeof(char *) * (count_word + 1));
    word_array = malloc_it(word_array, str, separator);
    return (my_fill_array(str, word_array, separator));
}
