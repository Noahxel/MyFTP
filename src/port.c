/*
** EPITECH PROJECT, 2023
** ftp
** File description:
** port
*/

#include "../includes/my_ftp.h"

void port_gestion(ftp_t *ftp, int j, char **cmd)
{
    struct sockaddr_in pasvSocket;
    int pasvFd = 0;
    int pasvLen = sizeof(pasvSocket);
    client_t client = ftp->clients[j];

    if (!cmd[1])
        return (put_messages(501, ftp->clients[j].clientFd));
    if ((pasvFd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        check_fail(ftp, "pasv: socket");
    memset(&pasvSocket, 0, sizeof(pasvSocket));
    pasvSocket.sin_family = AF_INET;
    pasvSocket.sin_port = atoi(cmd[1]);
    pasvSocket.sin_addr.s_addr = INADDR_ANY;
    if (bind(pasvFd, (struct sockaddr *)&pasvSocket, sizeof(pasvSocket)) < 0)
        check_fail(ftp, "bind");
    if (getsockname(pasvFd, (struct sockaddr *)
    &pasvSocket, (socklen_t *)&pasvLen) < 0)
        check_fail(ftp, "getsockname");
    put_messages(200, client.clientFd);
}
