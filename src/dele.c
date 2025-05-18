/*
** EPITECH PROJECT, 2023
** ftp
** File description:
** dele
*/

#include "../includes/my_ftp.h"

void dele_gestion(ftp_t *ftp, int i, char **cmd)
{
    int fd = ftp->clients[i].clientFd;
    char solved[BUFFSIZE];
    char *cleared = NULL;
    char *finalpath = NULL;
    char *copy = strdup(ftp->clients[i].persoPath);

    if (!cmd[1])
        return (put_messages(501, fd));
    if (cmd[1][0] != '/')
        cleared = my_strcat("/", cmd[1]);
    if (!realpath((finalpath = my_strcat(copy, cleared)), solved))
        return (put_messages(550, ftp->clients[i].clientFd));
    solved[strlen(solved)] = '\0';
    if (!strstr(solved, ftp->rootname))
        return (put_messages(550, ftp->clients[i].clientFd));
    if (remove(solved) < 0)
        return (put_messages(450, fd));
    put_messages(250, fd);
    free(finalpath);
    free(copy);
}
