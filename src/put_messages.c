/*
** EPITECH PROJECT, 2023
** ftp
** File description:
** put_messages
*/

#include "../includes/my_ftp.h"

void put_messages(int messCode, int clientFd)
{
    messCode == 120 ? write(clientFd, MSG120, strlen(MSG120)) : 0;
    messCode == 125 ? write(clientFd, MSG125, strlen(MSG125)) : 0;
    messCode == 150 ? write(clientFd, MSG150, strlen(MSG150)) : 0;
    messCode == 200 ? write(clientFd, MSG200, strlen(MSG200)) : 0;
    messCode == 220 ? write(clientFd, MSG220, strlen(MSG220)) : 0;
    messCode == 221 ? write(clientFd, MSG221, strlen(MSG221)) : 0;
    messCode == 226 ? write(clientFd, MSG226, strlen(MSG226)) : 0;
    messCode == 227 ? write(clientFd, MSG227, strlen(MSG227)) : 0;
    messCode == 230 ? write(clientFd, MSG230, strlen(MSG230)) : 0;
    messCode == 250 ? write(clientFd, MSG250, strlen(MSG250)) : 0;
    messCode == 257 ? write(clientFd, MSG257, strlen(MSG257)) : 0;
    messCode == 331 ? write(clientFd, MSG331, strlen(MSG331)) : 0;
    messCode == 332 ? write(clientFd, MSG332, strlen(MSG332)) : 0;
    messCode == 530 ? write(clientFd, MSG530, strlen(MSG530)) : 0;
    messCode == 500 ? write(clientFd, MSG500, strlen(MSG500)) : 0;
    messCode == 550 ? write(clientFd, MSG550, strlen(MSG550)) : 0;
    messCode == 501 ? write(clientFd, MSG501, strlen(MSG501)) : 0;
    messCode == 450 ? write(clientFd, MSG450, strlen(MSG450)) : 0;
    messCode == 214 ? write(clientFd, MSG214, strlen(MSG214)) : 0;
}

void put_custom(char *message, int clientFd)
{
    write(clientFd, message, strlen(message));
}
