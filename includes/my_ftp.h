/*
** EPITECH PROJECT, 2023
** ftp
** File description:
** my_ftp
*/

#ifndef MY_FTP_H_
    #define MY_FTP_H_
    #define BUFFSIZE 1024
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <sys/select.h>
    #include <stdbool.h>
    #include <fcntl.h>
    #include <dirent.h>
    #include <sys/stat.h>
    #define MSG125 "120 Data connection already open; transfer starting.\n"
    #define MSG120 "125 Service ready in nnn minutes\n"
    #define MSG150 "150 File status okay; about to open data connection.\n"
    #define MSG200 "200 Command okay.\n"
    #define MSG220 "220 Service ready for new user.\n"
    #define MSG221 "221 Service closing control connection.\n"
    #define MSG226 "226 Closing data connection.\n"
    #define MSG227 "227 Entering Passive Mode (h1,h2,h3,h4,p1,p2).\n"
    #define MSG230 "230 User logged in, proceed.\n"
    #define MSG250 "250 Requested file action okay, completed.\n"
    #define MSG257 "257 \"PATHNAME\" created."
    #define MSG331 "331 User name okay, need password.\n"
    #define MSG332 "332 Need account for login.\n"
    #define MSG530 "530 Not logged in.\n"
    #define MSG500 "500 Syntax error, command unrecognized.\n"
    #define MSG550 "550 Requested action not taken.\n"
    #define MSG501 "501 Syntax error in parameters or arguments.\n"
    #define MSG450 "450 Requested file action not taken.\n"
    #define MSG214 "214 Help message.\n"

typedef struct client_s {
    int clientFd;
    bool isAuth;
    bool havePass;
    bool isAnonym;
    char *persoPath;
    int persoSockFd;
    struct sockaddr_in persoSocket;
} client_t;

typedef struct ftp_s {
    client_t *clients;
    int port;
    int serverFd;
    struct sockaddr_in serverSocket;
    char *path;
    int nbClients;
    struct sockaddr_in clientSocket;
    socklen_t clientlen;
    char *globalPath;
    char *rootname;
} ftp_t;

void set_server(ftp_t *ftp);
void client_gestion(int serverSocketFd, int port);
void check_fail(ftp_t *ftp, char *error);
void get_clients_requests(ftp_t *ftp, fd_set rfds);
void put_messages(int messCode, int clientFd);
char **my_str_to_word_array(char *str, char separator);
void put_custom(char *msg, int clientFd);
void check_client_fail(ftp_t *ftp, int j, char *error);
void user_gestion(ftp_t *ftp, int j, char *buf);
void pass_gestion(ftp_t *ftp, int j, char *buf);
void pwd_gestion(ftp_t *ftp, int j);
void cdup_gestion(ftp_t *ftp, int j);
void cwd_gestion(ftp_t *ftp, int j, char **fullcmd, int msgcode);
void port_gestion(ftp_t *ftp, int j, char **cmd);
void pasv_gestion(ftp_t *ftp, int j);
char *my_strcat(char *dest, char *src);
void noop_gestion(ftp_t *ftp, int i);
void quit_gestion(ftp_t *ftp, int j);
void help_gestion(ftp_t *ftp, int i);
void dele_gestion(ftp_t *ftp, int i, char **cmd);

#endif /* !MY_FTP_H_ */
