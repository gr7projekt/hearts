/*
** Syn-Ack-Server för projektkursen Programvaruteknik, KTH Vt -16
** Johan Lipecki, 2016-05-04
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <syslog.h>
#include <pwd.h>
#include <signal.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "port_hearts.h"
#include "account.h"

/* Change this to whatever your daemon is called */
#define DAEMON_NAME "Hearts_SYN-ACK"

/* Change this to the user under which to run */
#define RUN_AS_USER "grupp 7"

#define FILENAME "/var/tmp/hearts_syn-ack.pid"

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define IP_ADDRESS "130.237.84.89"
#define PORT "1337"

void sigchld_handlr(int s)
{
while(waitpid(-1, NULL, WNOHANG) > 0);
}

void sigchld_handler(int s)
{
    switch(s) {
        case(SIGTSTP):  exit((long)SIG_IGN);  break;/* Various TTY signals */
        case(SIGTTOU):  exit((long)SIG_IGN);  break;
        case(SIGTTIN):  exit((long)SIG_IGN);  break;
        case(SIGHUP):   exit((long)SIG_IGN);  break;/* Ignore hangup signal */
        default:        exit((long)SIG_DFL);  break;
    }
}

void child_handler(int signum)
{

    switch(signum) {
        case SIGALRM:   exit(EXIT_FAILURE); break;
        case SIGUSR1:   syslog(LOG_INFO, "child_handler: SIGUSR1"); exit(EXIT_SUCCESS); break;
        case SIGCHLD:   exit(EXIT_FAILURE); break;
        default:        exit((long)SIG_DFL); break;
    }
}

int kill_server(void)
{
    int link;
    //remove the file so that another one may be created
    if((link=unlink(FILENAME))==-1){
       syslog(LOG_ERR, "unable to unlink file, code %d (%s)",
                errno, strerror(errno));
        exit(1);
    }
    return 0;
}

void daemonize(const char *lockfile)
{
    pid_t pid, sid, parent,child;
    int lfp = -1;
    FILE *pid_fp;
    struct sigaction act,old_act,act2;

    act.sa_handler=child_handler;
    sigemptyset (&act.sa_mask);
    act.sa_flags = 0;

    /* already a daemon */
    if (getppid() == 1 ) {
        syslog(LOG_ERR, "already a daemon! Code = %d (%s)\n",
                errno, strerror(errno));
        return;
    }
    //printf("Ready for the lockfile!\n");
    /* Create the lock file as the current user */
    if ( lockfile && lockfile[0] ) {
        lfp = open(lockfile,O_RDWR|O_CREAT,0640);   //|O_EXCL taken care of in the start-file
        if ( lfp < 0 ) {
            syslog( LOG_ERR, "unable to create lock file %s, code=%d (%s)\n",
                    lockfile, errno, strerror(errno) );
            exit(EXIT_FAILURE);
        }
    }
    //printf("lockfile done\n");

    /* Drop user if there is one, and we were run as root */
    if ( getuid() == 0 || geteuid() == 0 ) {
        struct passwd *pw = getpwnam(RUN_AS_USER);
        if ( pw ) {
            syslog( LOG_NOTICE, "setting user to " RUN_AS_USER );
            setuid( pw->pw_uid );
        }
    }

    /*
    Trap signals that we expect to recieve,  sighandler_t signal(int signum, sighandler_t handler)
    http://www.gnu.org/software/libc/manual/html_node/Sigaction-Function-Example.html
    */
    sigaction(SIGCHLD,&act,&old_act);
    sigaction(SIGUSR1,&act,&old_act);
    sigaction(SIGALRM,&act,&old_act);

    /* Fork off the parent process */
    pid = fork();
    if (pid < 0) {
        syslog( LOG_ERR, "unable to fork daemon, code=%d (%s)",
                errno, strerror(errno) );
        exit(EXIT_FAILURE);
    }
    /* If we got a good PID, then we can exit the parent process. */
    if (pid > 0) {

        /* Wait for confirmation from the child via SIGTERM or SIGCHLD, or
           for two seconds to elapse (SIGALRM).  pause() should not return. */
        alarm(2);
        pause();

        exit(EXIT_FAILURE);
    }

    /* At this point we are executing as the child process */
    if(!(pid_fp = fopen(FILENAME,"w"))){
        syslog(LOG_ERR,"pid_fd",strerror(errno));
        exit(EXIT_FAILURE);
    }

    fprintf(pid_fp,"%d\n",child = getpid()); //this writes the pid to revd.pid and ensures all other data is wiped
    fclose(pid_fp);

    /* Cancel certain signals */
    sigaction(SIGTSTP,&act2,NULL); /* Various TTY signals */
    sigaction(SIGTTOU,&act2,NULL);
    sigaction(SIGTTIN,&act2,NULL);
    sigaction(SIGHUP,&act2,NULL);
    sigaction(SIGTERM,&act2,NULL);

    /* Change the file mode mask */
    //printf("umask!\n");
    umask(0);

    /* Create a new SID for the child process */
    sid = setsid();
    if (sid < 0) {
        syslog( LOG_ERR, "unable to create a new session, code %d (%s)",
                errno, strerror(errno) );
        exit(EXIT_FAILURE);
    } //else syslog(LOG_INFO, "sid ok!");

    /* Change the current working directory.  This prevents the current
       directory from being locked; hence not being able to remove it. */
    if ((chdir("/")) < 0) {
        syslog( LOG_ERR, "unable to change directory to %s, code %d (%s)",
                "/", errno, strerror(errno) );
        exit(EXIT_FAILURE);
    }
    //printf("directory changed\n");

    /* Redirect standard files to /dev/null */
    freopen("/dev/null", "r", stdin);
    freopen("/dev/null", "w", stdout);
    freopen("/dev/null", "w", stderr);

    /* Tell the parent process that we are A-okay */
    kill(getppid(),SIGUSR1);
    syslog(LOG_INFO, "parent killed!");
}

int main(int argc,char const *argv[])
{
    int done, len, n, pid, s, s2, t, inet_fd, connections=0;
    struct sockaddr_in inet, inet2;
    struct hostent* hostinfo;
    char arguments[100],hearts_start[140];
    memset(arguments,'\0',sizeof(arguments));
    memset(str,'\0',sizeof(str));

    /* Initialize the logging interface */
    openlog(DAEMON_NAME, LOG_PID, LOG_LOCAL5 );
    syslog(LOG_INFO, "starting" );

    /* Daemonize */
    daemonize( "/var/lock/" DAEMON_NAME);
    syslog(LOG_INFO, "We did get to daemonize!\n");

    /* Now we are a daemon -- do the work for which we were paid */
    // Example from Beej's Guide to Network Programming:
    ////https://beej.us/guide/bgnet/output/html/multipage/sockaddr_inman.html

    if ((inet_fd = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
        syslog(LOG_ERR, "%s", strerror(errno));
        exit(1);
    } else syslog(LOG_INFO, IP_ADDRESS);

    inet.sin_family = AF_INET;
    inet.sin_port = htons(atoi(PORT));
    inet_pton(AF_INET,IP_ADDRESS,&inet.sin_addr);
    /*(strcpy(inet.sin_path, argv[1]));
    syslog(LOG_INFO, "path copied!\n");

    if(unlink(inet.sin_path)){
        syslog(LOG_ERR, strerror(errno));
        exit(1);
    } else syslog(LOG_INFO, "path unlinked!\n");*/

    //len = strlen(local.sun_path) + sizeof(local.sun_family);
    if (bind(inet_fd, (struct sockaddr *)&inet, sizeof inet) == -1) {
        syslog(LOG_ERR, strerror(errno));
        exit(1);
    } else syslog(LOG_INFO, "socket bound!\n");

    if (listen(inet_fd, 8) == -1) {
        syslog(LOG_ERR, strerror(errno));
        exit(1);
    }
    syslog(LOG_INFO, "listening for up to 8 connections!\n");

    for(connections=0;;connections++) {
        //signalhantering, kunde kanske vara utanför loopen men varför ändra ett vinnande koncept?
        int connection_no = (connections%4);
        struct sigaction sa;
        sa.sa_handler = sigchld_handlr; // reap all dead processes
        sigemptyset(&sa.sa_mask);
        sa.sa_flags = SA_RESTART;
        if (sigaction(SIGCHLD, &sa, NULL) == -1) {      //WNOHANG!
            syslog(LOG_ERR, strerror(errno));
            exit(1);
        }
        //syslog(LOG_INFO, "Waiting for a connection...\n");
        t = sizeof(inet2);
        if ((s2 = accept(inet_fd, (struct sockaddr *)&inet2, &t)) == -1) {
          syslog(LOG_ERR, strerror(errno));
          exit(1);
        }
        /* fork efter acceptet! */
        if((pid=fork())==-1){                                   // fork och felhantering
            syslog(LOG_ERR, strerror(errno));
            exit(1);
        }
        else if(!pid){                                          //serverbarnet ärver accepten, socketen och fildeskriptorn.
            //printf("Connected.\n");
            i = 0,j=0, r;
            done = 0;
            Account account;
            do {
                r = recv(s2, arguments,100, 0);
                if (r <= 0) {
                    if (r < 0) perror("recv");
                    done = 1;                                   //försäkrar oss om att accept-loopen avslutas nedan ...
                }                                               //om recv returnerar 0 eller -1.
                
                /*
                while(i) {
                    // You get three tries to login
                    if((account=prompt_for_login(&s2)) < 0){
                        j += 1;
                        if (j==3){ 
                            strcpy(arguments,"login failed");
                            if (send(s2,arguments,30,0) < 0) syslog(LOG_ERR,"%s",strerror(errno));
                            close(s2);
                            exit(EXIT_FAILURE);
                        }
                        else continue;
                    }
                    else {
                        if((connection_no) == 0) memset(guid,'\0',4);
                        guid[connection_no] = assign_guid();
                        if((connection_no) == 3) {
                            if(start_game_server(&port, &guid) < 0){
                                syslog(LOG_ERR,"%s",strerror(errno));
                                send(s2,"game failed, try again",sizeof("game failed, try again"));
                                syslog(LOG_INFO,"game start failed");
                            }
                        }
                 
                 
                        else
                 
                 
                    }break;
                }*/
                
                if (!done){                                     //Inget fel eller avslut, enligt tilldelning
                    syslog(LOG_INFO, "!done\n");
                    if(!(syn_ack(arguments,&i,s2,port,connection_no))){
                        strcpy(arguments,"ENDOFTRANS");
                        if (send(s2,arguments,30,0) < 0) {  //meddela att meddelandet är klart
                            syslog(LOG_ERR,"%s",strerror(errno);
                            done = 1;                   //försäkrar oss om att accept-loopen avslutas
                        }
                        else done = 0;
                        memset(arguments,'\0',sizeof(arguments));
                    }
                } i += 1;
            } while (!done);                        //så länge klienten skickar data håller vi öppet 24/7
            printf("I'm server %d and my client just signed off!\n",getpid());
            syslog(LOG_NOTICE, "terminated" );
            closelog();
            exit(0);
        }
        else close(s2);
        //if((wate=waitpid(0,NULL,WNOHANG))==-1)perror("waitpid\n");
    }
    /* Finish up */
    if((kill_server())){
        syslog(LOG_ERR, "Server process not terminated. Pid file %, code = %d, error: %s",
               FILENAME, errno, strerror(errno));
               exit(EXIT_FAILURE);
    }   else     syslog(LOG_NOTICE, "terminated" );
    closelog();
    return 0;
}



