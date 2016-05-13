//
//  port_hearts.c
//  
//
//  Created by Johan Lipecki on 2016-04-20.
//
//

#include "port_hearts.h"

uint32_t getIP(char *str)
{
	
	return 0;
}

int start_game_server(int port){
    char static hearts_start[200];
    sprintf(hearts_start, "%s %s", GAME_SERVER, port);
    return system(hearts_start);
}
int get_random_port_number(void){
    srandom((unsigned)time(NULL));
    return (random()%10000 + 40000);
}
int syn_ack(char* arguments, int *i,int sd, char *port, int connection_no){
    if(strcmp(arguments,"ENDOFTRANS")){
        syslog(LOG_INFO, "syn-ack argument %d: %s",*i, arguments);
        
        if (!strcmp(arguments, "hearts") && !(*i)) strcpy(arguments,"diamonds");
        
        else if(!(strcmp(arguments, "port")) && (*i)){
            
            sprintf(arguments, "%s %d", port, connection_no);
        }
        else strcpy(arguments, "This incident will be reported!");
        
        //skicka tillbaka strängen
        if (send(sd,arguments,100,0) < 0) {
            syslog(LOG_ERR, "%s", strerror(errno));
        }
    return 0;
    }
}
Account prompt_for_login(int *socketDescriptor) {
    static Account account;
    char arguments[100];
    char *account_values[10];
    strcpy(account.username, NULL);
    if (0 > send(*socketDescriptor, "account", sizeof("account")+1, 0)) {
        syslog(LOG_ERR, "%s", strerror(errno));
        return account;
    }
    if (0 > recv(*socketDescriptor, arguments, 101, 0)) {
        syslog(LOG_ERR, "%s", strerror(errno));
        return account;
    }
    strcpy(account_values,separate_strings(arguments, ";"));
    strcpy(account.username,account_values[0]);
    strcpy(account.password,account_values[1]);
    if ((account.username == getAccountByUsername(account.username).username) &&
            (account.password == getAccountByUsername(account.username).password)) account = getAccountByUsername(account_values[0]);
    return account;
}

char* separate_strings(char *inputstring, char *separators) {
    //From strsep() manual:
    // The following uses strsep() to parse a string,
    // containing tokens delimited by *separators, into an argument vector:
    char **ap, *list[10];

    for (ap = list; (*ap = strsep(&inputstring, (const char *) *separators)) != NULL;)
        if (**ap != '\0') if (++ap >= &list[10]) break;
    return *list;
}

