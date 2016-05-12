#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <signal.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include "SDL2/SDL_net.h"
#include "SDL2/SDL.h"


int init_net();

int main(int argc, char *argv[])
{
	if (init_net()) printf("Success on init\n");
	pthread_t threads[4];
	int i = 0;
	for(;i < 4; i++)
		pthread_create(&threads[i], NULL, player_waits_or_plays, &i);
	return 0;
}


int init_net()
{
        if (SDLNet_Init() < 0) {
                printf("SDLNet_Init: %s", SDLNet_GetError());
                return 0;
        }
        else return 1;
}
