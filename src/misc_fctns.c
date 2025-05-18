/*
** EPITECH PROJECT, 2023
** ftp
** File description:
** misc_fctns
*/

#include "../includes/my_ftp.h"

void quit_gestion(ftp_t *ftp, int j)
{
    int k = 0;
    client_t *temp = ftp->clients;

    ftp->clients = realloc(ftp->clients, sizeof(client_t) * ftp->nbClients);
    put_messages(221, ftp->clients[j].clientFd);
    close(ftp->clients[j].clientFd);
    for (int i = 0; i < ftp->nbClients; i++) {
        if (i == j)
            continue;
        ftp->clients[k] = temp[i];
        k++;
    }
    ftp->nbClients--;
}

void noop_gestion(ftp_t *ftp, int i)
{
    put_messages(200, ftp->clients[i].clientFd);
}
