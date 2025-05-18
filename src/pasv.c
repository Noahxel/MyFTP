/*
** EPITECH PROJECT, 2023
** ftp
** File description:
** pasv
*/

#include "../includes/my_ftp.h"

void put_socket_bytes(client_t client, int pasvPort)
{
    char buff[256];
    in_addr_t server_ip;

    sprintf(buff, "227 Entering Passive Mode (%d,%d,%d,%d,%d,%d)\n",
    (int)(server_ip) & 0xff,
    (int)((server_ip) >> 8) & 0xff,
    (int)((server_ip) >> 16) & 0xff,
    (int)((server_ip) >> 24) & 0xff,
    (int)(pasvPort >> 8), (int)(pasvPort & 0xff));
    put_custom(buff, client.clientFd);
}

void pasv_gestion(ftp_t *ftp, int j)
{
    struct sockaddr_in pasvSocket;
    int pasvFd = 0;
    int port = 0;
    int pasvLen = sizeof(pasvSocket);
    client_t client = ftp->clients[j];

    if ((pasvFd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        check_fail(ftp, "pasv: socket");
    memset(&pasvSocket, 0, sizeof(pasvSocket));
    pasvSocket.sin_family = AF_INET;
    pasvSocket.sin_port = 0;
    pasvSocket.sin_addr.s_addr = INADDR_ANY;
    if (bind(pasvFd, (struct sockaddr *)&pasvSocket, sizeof(pasvSocket)) < 0)
        check_fail(ftp, "bind");
    if (getsockname(pasvFd, (struct sockaddr *)
    &pasvSocket, (socklen_t *)&pasvLen) < 0)
        check_fail(ftp, "getsockname");
    port = ntohs(pasvSocket.sin_port);
    put_socket_bytes(client, port);
}
