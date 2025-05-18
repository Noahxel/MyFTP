/*
** EPITECH PROJECT, 2023
** ftp
** File description:
** main
*/

#include "../includes/my_ftp.h"

int handle_error(int argc, char **argv)
{
    (void)argv;
    char *reel = NULL;

    if (argc != 3) {
        perror("not enought arguments:\n\t./myftp [PORT] [PATH]\n");
        return (84);
    }
    if (!opendir(argv[2]))
        return (84);
    if (!realpath(argv[2], reel))
        return (84);
    return (0);
}

void set_ftp_struct(char **argv, ftp_t *ftp)
{
    char whereami[BUFFSIZE];

    getcwd(whereami, BUFFSIZE);
    ftp->clients = NULL;
    ftp->nbClients = 0;
    ftp->port = atoi(argv[1]);
    ftp->clientlen = sizeof(ftp->clientSocket);
    ftp->globalPath = strdup(whereami);
    ftp->rootname = argv[2];
}

int main(int argc, char **argv)
{
    (void)argc;
    int check = handle_error(argc, argv);
    ftp_t ftp;

    if (check == 84)
        return (84);
    if ((ftp.serverFd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        check_fail(&ftp, "server: socket");
    chdir(argv[2]);
    set_ftp_struct(argv, &ftp);
    set_server(&ftp);
    return (0);
}
