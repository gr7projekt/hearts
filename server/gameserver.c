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
#include "players.h"


int init_net();

int main(int argc, char *argv[])
{
	// receives hearts_start, "%s %s %s %s %s %s", GAME_SERVER, port, guid[0],guid[1],guid[2],guid[3]

	if (init_net()) printf("Success on init\n");
	pthread_t threads[4];
	int i = 0;
	for(;i < 4; i++) {
		char guid[33];
		char *arguments[2];
		sprintf(*arguments[0],"%d",i);
		//strcpy(arguments[1],guid[i]);
		pthread_create(&threads[i], NULL, player_waits_or_plays, arguments);
	}
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
