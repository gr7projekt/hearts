#ifndef RECIEVE_H_INCLUDED
#define RECIEVE_H_INCLUDED

#include "includes.h"

void seperate(char *trick[],char recieved_trick[],char tmp[],int *starting_player);

void getIP(char ip[]);

void recievehand(char recieved_trick[], Player p1[], char IP_ADDRESS[]);

void receiveontable(char recievetable[], Player p1[], char IP_ADDRESS[]);

#endif //RECIEVE_H_INCLUDED
