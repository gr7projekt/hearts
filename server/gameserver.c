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
	// receives hearts_start, "%s %s %s %s %s %s", GAME_SERVER, port, ipv4 array

	if (init_net()) printf("Success on init\n");
	pthread_t threads[4];
	Args thread_arg[4];
	__uint16_t port = htons((__uint16_t) argv[1]);
	__uint32_t ipv4 = htonl("localhost");
	char *trick[4];
	int i = 0;

	for(i = 0;i < 4; i++) {
		thread_arg[i].pos = i;
		thread_arg[i].address.port = port;
		thread_arg[i].address.host = ipv4;
		strcpy(*thread_arg[i].trick,*trick);
		pthread_create(&threads[i], NULL, player_waits_or_plays, (void *) &thread_arg[i]);
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
