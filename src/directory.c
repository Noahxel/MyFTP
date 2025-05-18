/*
** EPITECH PROJECT, 2023
** ftp
** File description:
** directory
*/

#include "../includes/my_ftp.h"


void pwd_gestion(ftp_t *ftp, int j)
{
    char *path = ftp->clients[j].persoPath;
    char str1[] = "257 \"";
    char str2[] = "\" created.\n";
    char final[100];

    if (strcmp(path, ftp->globalPath) == 0)
        path = "/";
    else {
        for (int i = 0; path[0] == ftp->globalPath[i]; i++)
            path++;
    }
    if (strcmp(path, "") == 0)
        path = "/";
    strcpy(final, str1);
    strcat(final, path);
    strcat(final, str2);

    put_custom(final, ftp->clients[j].clientFd);
}

void cdup_gestion(ftp_t *ftp, int j)
{
    char **fcmd = malloc(sizeof(char *) * 2);
    fcmd[0] = strdup("CWD");
    fcmd[1] = strdup("..");
    cwd_gestion(ftp, j, fcmd, 200);
    free(fcmd[0]);
    free(fcmd[1]);
    free(fcmd);
}

void cwd_gestion(ftp_t *ftp, int j, char **cmd, int msgcode)
{
    char solved[BUFFSIZE];
    char *cleared = NULL;
    char *copy = strdup(ftp->clients[j].persoPath);

    cleared = (cmd[1] && cmd[1][0] != '/' ? my_strcat("/", cmd[1]) : cmd[1]);
    if (!cmd[1])
        ftp->clients[j].persoPath = ftp->globalPath;
    else {
        if (!realpath(my_strcat(copy, cleared), solved))
            return (put_messages(550, ftp->clients[j].clientFd));
        solved[strlen(solved)] = '\0';
        if (!strstr(solved, ftp->rootname))
            return (put_messages(550, ftp->clients[j].clientFd));
        else {
            ftp->clients[j].persoPath = strdup(solved);
        }
    }
    put_messages(msgcode, ftp->clients[j].clientFd);
}
