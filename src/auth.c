/*
** EPITECH PROJECT, 2023
** ftp
** File description:
** auth
*/

#include "../includes/my_ftp.h"

void pass_gestion(ftp_t *ftp, int j, char *buf)
{
    if (ftp->clients[j].isAnonym && strcmp(buf, "PASS ") == 0) {
        ftp->clients[j].isAuth = true;
        return (put_messages(230, ftp->clients[j].clientFd));
    }
    if (!ftp->clients[j].isAnonym || strcmp(buf, "PASS ") != 0)
        return (put_messages(530, ftp->clients[j].clientFd));
    put_messages(332, ftp->clients[j].clientFd);
}

void user_gestion(ftp_t *ftp, int j, char *buf)
{
    if (strcmp(buf, "USER Anonymous") == 0) {
        ftp->clients[j].isAnonym = true;
    }
    put_messages(331, ftp->clients[j].clientFd);
}
