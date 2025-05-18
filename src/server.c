/*
** EPITECH PROJECT, 2023
** ftp
** File description:
** server
*/

#include "../includes/my_ftp.h"

void add_client(ftp_t *ftp, int clientFd)
{
    put_messages(220, clientFd);
    ftp->clients = realloc(ftp->clients,
    sizeof(client_t) * (ftp->nbClients + 1));
    ftp->clients[ftp->nbClients].clientFd = clientFd;
    ftp->clients[ftp->nbClients].isAuth = false;
    ftp->clients[ftp->nbClients].isAnonym = false;
    ftp->clients[ftp->nbClients].persoPath = strdup(ftp->globalPath);
    ftp->clients[ftp->nbClients].persoSockFd = -1;
    ftp->nbClients++;
}

int accept_max(ftp_t *ftp, int max)
{
    int clientFd = accept(ftp->serverFd, (struct sockaddr *)
    &ftp->clientSocket, (socklen_t *)&ftp->clientlen);

    if (clientFd < 0)
        check_fail(ftp, "accept");
    else
        add_client(ftp, clientFd);
    if (clientFd > max)
        max = clientFd;
    return (max);
}

void debug_printer(ftp_t *ftp, int max)
{
    printf("##########     DEBUG     ##########\n");
    printf("looped:\nfd_clients = [[");
    for (int i = 0; i < ftp->nbClients; i++) {
        printf("%d", ftp->clients[i].clientFd);
        if (i != ftp->nbClients - 1)
            printf("], [");
    }
    printf("]]\n");
    printf("len fd_clients = %d\n", ftp->nbClients);
    printf("max = %d\n", max);
    printf("##################################\n\n");
}

void server_loop(ftp_t *ftp)
{
    int max = ftp->serverFd;
    fd_set rfds;

    while (1) {
        FD_ZERO(&rfds);
        FD_SET(ftp->serverFd, &rfds);
        for (int i = 0; i < ftp->nbClients; i++)
            FD_SET(ftp->clients[i].clientFd, &rfds);
        if (select(max + 1, &rfds, NULL, NULL, NULL) < 0)
            check_fail(ftp, "select");
        if (FD_ISSET(ftp->serverFd, &rfds))
            max = accept_max(ftp, max);
        get_clients_requests(ftp, rfds);
    }
    check_fail(ftp, NULL);
}

void set_server(ftp_t *ftp)
{
    struct sockaddr_in socket;

    memset(&socket, 0, sizeof(socket));
    socket.sin_family = AF_INET;
    socket.sin_port = htons(ftp->port);
    socket.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(ftp->serverFd, (struct sockaddr *)&socket, sizeof(socket)) < 0)
        check_fail(ftp, "bind");
    if (listen(ftp->serverFd, SOMAXCONN) < 0)
        check_fail(ftp, "listen");
    ftp->serverSocket = socket;
    server_loop(ftp);
}
