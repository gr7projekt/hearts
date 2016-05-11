//
//  port_hearts.h
//  
//
//  Created by Johan Lipecki on 2016-04-20.
//
//

#ifndef port_hearts_h
#define port_hearts_h

#define SYN0 "hearts"
#define ACK0 "diamonds"
#define SYN1 "port"

#define GAME_SERVER "./game_server"

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define PARENT 1

#include <stdio.h>

// Forks a game server if provided with a port number and an array of 4 guids,
// returns what system(3) returns, -1 indicates an error.
int start_game_server(char *,char *[]);
// Checks string for SYN0 if second argument points to a 0 and checks for SYN1 if second argument doesn't point to a 0
// Using the socket descriptor in the third argument, ACK0 is returned to the socket for SYN0
// arguments 4 and 5 are returned to the socket for SYN1
int syn_ack(char *,int*,int,char*,int);
// Returns a random number between 40 k and 50 k
int get_random_port_number(void);
// Sends the string "login" using provided socket descriptor pointer and send(2)
// Receives an Account struct using recv(2) and returns it on success.
// A negative value is returned on failure.
Account prompt_for_login(int*);
long assign_guid(void);

#endif /* port_hearts_h */
