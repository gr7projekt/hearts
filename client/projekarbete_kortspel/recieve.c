#include "recieve.h"

void seperate(char *trick[],char recieved_trick[],char tmp[])
{
    for(int i = 0;i <4; i++){
        tmp[0] = recieved_trick[i*3];
        tmp[1] = recieved_trick[i*3+1];
        tmp[2] = recieved_trick[i*3+2];
        tmp[3] = '\0';

        trick[i] = strdup(tmp);
    }
}
