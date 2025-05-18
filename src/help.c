/*
** EPITECH PROJECT, 2023
** ftp
** File description:
** help
*/

#include "../includes/my_ftp.h"

void help_gestion(ftp_t *ftp, int i)
{
    int fd = 0;
    struct stat len;
    char *buffer;
    char *filepath = "../help.txt";

    if ((fd = open(filepath, O_RDONLY)) < 0)
        check_client_fail(ftp, i, "open help message");
    stat(filepath, &len);
    buffer = malloc((len.st_size + 1) * sizeof(char));
    buffer[len.st_size] = '\0';
    read(fd, buffer, len.st_size);
    put_messages(214, ftp->clients[i].clientFd);
    put_custom(buffer, ftp->clients[i].clientFd);
    close (fd);
    free(buffer);
}
