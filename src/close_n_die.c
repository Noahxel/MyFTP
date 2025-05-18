/*
** EPITECH PROJECT, 2023
** ftp
** File description:
** main
*/

#include "../includes/my_ftp.h"

void check_fail(ftp_t *ftp, char *error)
{
    if (error)
        perror(error);
    if (ftp) {
        if (ftp->serverFd != -1)
            close(ftp->serverFd);
        for (int i = 0; i < ftp->nbClients; i++)
            close(ftp->clients[i].clientFd);
        if (ftp->clients)
            free(ftp->clients);
    }
    exit(84);
}

void check_client_fail(ftp_t *ftp, int j, char *error)
{
    int k = 0;
    client_t *temp = ftp->clients;

    if (error)
        perror(error);
    ftp->clients = realloc(ftp->clients, sizeof(client_t) * ftp->nbClients);
    close(ftp->clients[j].clientFd);
    for (int i = 0; i < ftp->nbClients; i++) {
        if (i == j)
            continue;
        ftp->clients[k] = temp[i];
        k++;
    }
    ftp->nbClients--;
}
