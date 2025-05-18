/*
** EPITECH PROJECT, 2021
** my_strcat
** File description:
** This code will concatenate two strings
*/

#include "../includes/my_ftp.h"
#include <stdio.h>
#include <stdlib.h>

char *my_strcpy(char *dest , char const *src)
{
    int i = 0;

    while (src[i] != '\0') {
        dest[i] = src[i];
        i = i + 1;
    }
    dest[i] = '\0';
    return (dest);
}

char *my_strcat(char *dest, char *src)
{
    int b = strlen(dest);
    int a = strlen(src);
    int totalen = b + a;
    char *final = malloc(sizeof(char) * (totalen + 1));

    final = my_strcpy(final, dest);
    for (int i = 0; b < totalen; i++) {
        final[b] = src[i];
        b++;
    }
    final[b] = '\0';
    return (final);
}
