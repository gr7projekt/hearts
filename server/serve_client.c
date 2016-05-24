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
#include "game.h"
#include "players.h"

#define BUFLEN 512
#define NPACK 4
#define GAMEPORT 41337

void diep(char *s) {
    perror(s);
    exit(EXIT_FAILURE);
}
// from UDP made simple at https://www.abc.se/~m6695/udp.html
int main(void) {
	

	struct sockaddr_in si_me, si_other;
	int s, i;
	ssize_t len;
	socklen_t slen=sizeof(si_other);
	FILE *fd;
	fd = fopen("/var/tmp/serve_client","w");
	char buf[BUFLEN]={"start"};
	char *trick[4];
	FF_trick(trick);
	char trick_to_send[20];
	for(int i =0; i<4;i++) {
		if (!i) {
			strcpy(trick_to_send, trick[i]);
			strcat(trick_to_send, ";");
		}
		else {
			strcat(trick_to_send,trick[i]);
			strcat(trick_to_send,";");
		}
		printf(fd,"done with trick!\n");
	}
	if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1)
		diep("socket");
	printf("socket open\n");
	memset((char *) &si_me, 0, sizeof(si_me));
	si_me.sin_family = AF_INET;
	si_me.sin_port = htons(GAMEPORT);
	si_me.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(s, &si_me, sizeof(si_me))==-1)
		diep("bind");
	printf("bound\n");
	void *buffer = (void *) strdup(buf);
	while(strcmp(buffer,"quit")){
		printf("buffer: %s \n",buf);
		if ((len=recvfrom(s, buffer, BUFLEN, 0, &si_other, &slen))==-1) diep("recvfrom()");
		printf("Received packet from %s:%d\nData: %s\nLength: %d\n",
		       inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port), (char *) buffer,(int) len);
		for (i=3; i<NPACK; i++) {
			printf("Sending packet %s\n", trick[i]);
			sprintf(buf, "This is packet %d\n", i);
			if (sendto(s, (char *) trick_to_send, BUFLEN, 0, &si_other,  slen)==-1)
				diep("sendto()");
			}
	}
	printf("the end!");
    	close(s);
    	return 0;
}


/*
 * #include <stdio.h>
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
#include "game.h"
#include "players.h"

#define BUFLEN 512
#define NPACK 4
#define GAMEPORT 41337

void diep(char *s) {
    perror(s);
    exit(EXIT_FAILURE);
}
// from UDP made simple at https://www.abc.se/~m6695/udp.html
int main(void) {


	struct sockaddr_in si_me, si_other;
	int s, i;
	ssize_t len;
	socklen_t slen=sizeof(si_other);
	FILE *fd;
	fd = fopen("/var/tmp/serve_client","w");
	char buf[BUFLEN]={"start"};
	char *trick[4];
	FF_trick(trick);
	char trick_to_send[20];
	for(int i =0; i<4;i++) {
		if (!i) {
			strcpy(trick_to_send, trick[i]);
			strcat(trick_to_send, ";");
		}
		else {
			strcat(trick_to_send,trick[i]);
			strcat(trick_to_send,";");
		}
		fprintf(fd,"done with trick!\n");
	}
	if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1)
		diep("socket");
	printf("socket open\n");
	memset((char *) &si_me, 0, sizeof(si_me));
	si_me.sin_family = AF_INET;
	si_me.sin_port = htons(GAMEPORT);
	si_me.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(s, &si_me, sizeof(si_me))==-1)
		diep("bind");
	printf("bound\n");
	void *buffer = (void *) strdup(buf);
	while(strcmp(buffer,"quit")){
		printf("buffer: %s \n",buf);
		if ((len=recvfrom(s, buffer, BUFLEN, 0, &si_other, &slen))==-1) diep("recvfrom()");
		printf("Received packet from %s:%d\nData: %s\nLength: %d\n",
		       inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port), (char *) buffer,(int) len);
		for (i=3; i<NPACK; i++) {
			printf("Sending packet %s\n", trick[i]);
			sprintf(buf, "This is packet %d\n", i);
			if (sendto(s, (char *) trick_to_send, BUFLEN, 0, &si_other,  slen)==-1)
				diep("sendto()");
			}
	}
	printf("the end!");
    	close(s);
    	return 0;
}

 */