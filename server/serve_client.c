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
#include <SDL_net.h>
#include <SDL.h>
#include "players.h"
#include "port_hearts.h"

#define BUFLEN 512
#define NPACK 4
#define GAMEPORT 41337

void diep(char *s) {
    perror(s);
    exit(1);
}
// from UDP made simple at https://www.abc.se/~m6695/udp.html
int main(void) {
	struct sockaddr_in si_me, si_other;
	int s, i, slen=sizeof(si_other);
	char buf[BUFLEN];
	char *trick[] = {"02","00","2A","1C"};
	char trick_to_send[20];
	for(int i =0; i<NPACK;i++) {
		if (!i) strcpy(trick_to_send, trick[i]);
		else {
			strcat(trick_to_send,";");
			strcat(trick_to_send,trick[i]);
		}
	}
	if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1)
		diep("socket");

	memset((char *) &si_me, 0, sizeof(si_me));
	si_me.sin_family = AF_INET;
	si_me.sin_port = htons(GAMEPORT);
	si_me.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(s, &si_me, sizeof(si_me))==-1)
		diep("bind");

	for (i=3; i<NPACK; i++) {
		if (recvfrom(s, buf, BUFLEN, 0, &si_other, &slen)==-1)
			diep("recvfrom()");
		printf("Received packet from %s:%d\nData: %s\n\n",
		       inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port), buf);
	}
	for (i=0; i<NPACK; i++) {
		printf("Sending packet %s\n", trick[i]);
		sprintf(buf, "This is packet %d\n", i);
		if (sendto(s, buf, BUFLEN, 0, &si_other, slen)==-1)
			diep("sendto()");
		}

    	close(s);
    	return 0;
}
int init_net();

void test(int argc,char *argv[])
{
	// receives hearts_start, "%s %s %s %s %s %s", GAME_SERVER, port, ipv4 array
	Trick *trick1;
	IPaddress iPaddress;

	if (init_net()) printf("Success on init\n");
	__uint16_t port = htons((__uint16_t) argv[1]);
	__uint32_t ipv4 = htonl((__uint32_t)IP_ADDRESS);

	iPaddress.host = ipv4;
	iPaddress.port = port;
	trick1->address = iPaddress;

	char *trick[] = {"02","00","2A","1C"};
	for(int i=0;i<4;i++) strcpy(trick1->trick[i],trick[i]);
	// Bind address to the first free channel
	// UDPsocket udpsock;
	// IPaddress *address;
	int chanL=0, mottagna_paket=0;
	char str[40] = {'\0'};
	sprintf(str,"%s;%s;%s;%s;",trick1->trick[0],trick1->trick[1],trick1->trick[2],trick1->trick[3]);

	// create a UDPsocket on port
	UDPsocket udPsocket;

	if(!(udPsocket=SDLNet_UDP_Open(iPaddress.port))){
		printf("SDLNet_UDP_Open: %s\n", SDLNet_GetError());
		exit(2);
	}
	uint8_t *string=0;
	strcpy(string,str);
	UDPpacket skicka_hand = createPacket(chanL,string,sizeof(str),100,0,iPaddress);
	UDPpacket mottaget_paket;

	if ((chanL = SDLNet_UDP_Bind(udPsocket, -1, &iPaddress)) < 0) {
		syslog(LOG_ERR, "SDLNet_UDP_Bind: %s\n", SDLNet_GetError());
		// do something because we failed to bind
	}

}


int init_net()
{
        if (SDLNet_Init() < 0) {
                printf("SDLNet_Init: %s", SDLNet_GetError());
                return 0;
        }
        else return 1;

}
