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

int main(int argc, char *argv[])
{
    if(atoi(argv[1]) >= 40000 && atoi(argv[1]) <= 50000)
    {
        printf("%s\n", argv[1]);
    }
    return 0;
}