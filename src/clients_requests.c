/*
** EPITECH PROJECT, 2023
** ftp
** File description:
** clientsRequests
*/

#include "../includes/my_ftp.h"

bool cmd_is_valid(char *cmd)
{
    if (strcmp(cmd, "USER") == 0 || strcmp(cmd, "PASS") == 0 ||
        strcmp(cmd, "QUIT") == 0 || strcmp(cmd, "CWD") == 0 ||
        strcmp(cmd, "CDUP") == 0 || strcmp(cmd, "QUIT") == 0 ||
        strcmp(cmd, "PWD") == 0 || strcmp(cmd, "PASV") == 0 ||
        strcmp(cmd, "PORT") == 0 || strcmp(cmd, "NOOP") == 0 ||
        strcmp(cmd, "HELP") == 0 || strcmp(cmd, "DELE") == 0) {
        return (true);
    }
    return (false);
}

void connected_commands(ftp_t *ftp, int i, char **cmd)
{
    strcmp(cmd[0], "CWD") == 0 ? cwd_gestion(ftp, i, cmd, 250) : 0;
    strcmp(cmd[0], "CDUP") == 0 ? cdup_gestion(ftp, i) : 0;
    strcmp(cmd[0], "QUIT") == 0 ? quit_gestion(ftp, i) : 0;
    strcmp(cmd[0], "PWD") == 0 ? pwd_gestion(ftp, i) : 0;
    strcmp(cmd[0], "PASV") == 0 ? pasv_gestion(ftp, i) : 0;
    strcmp(cmd[0], "PORT") == 0 ? port_gestion(ftp, i, cmd) : 0;
    strcmp(cmd[0], "NOOP") == 0 ? noop_gestion(ftp, i) : 0;
    strcmp(cmd[0], "DELE") == 0 ? dele_gestion(ftp, i, cmd) : 0;
    strcmp(cmd[0], "HELP") == 0 ? help_gestion(ftp, i) : 0;
}

void manage_clients_request(ftp_t *ftp, int i, char *buf)
{
    char **cmd = my_str_to_word_array(buf, ' ');

    if (!cmd_is_valid(cmd[0]) && strlen(buf) != 0)
        return (put_messages(500, ftp->clients[i].clientFd));
    if (!ftp->clients[i].isAuth && strlen(buf) != 0) {
        if (strcmp(cmd[0], "USER") == 0)
            return (user_gestion(ftp, i, buf));
        if (strcmp(cmd[0], "PASS") == 0)
            return (pass_gestion(ftp, i, buf));
        if (strcmp(cmd[0], "QUIT") == 0)
            return (quit_gestion(ftp, i));
        if (strcmp(cmd[0], "HELP") == 0)
            return (help_gestion(ftp, i));
        return (put_messages(530, ftp->clients[i].clientFd));
    } else
        connected_commands(ftp, i, cmd);
}

void get_clients_requests(ftp_t *ftp, fd_set rfds)
{
    char buf[BUFFSIZE];
    int r = 0;

    for (int i = 0; i < ftp->nbClients; i++) {
        if (!FD_ISSET(ftp->clients[i].clientFd, &rfds))
            continue;
        if ((r = read(ftp->clients[i].clientFd, &buf, BUFFSIZE)) > 0) {
            buf[r - 2] = '\0';
            manage_clients_request(ftp, i, buf);
            memset(buf, 0, BUFFSIZE);
            r = 0;
        }
        if (r < 0)
            check_fail(ftp, "read client buffer:");
    }
}
