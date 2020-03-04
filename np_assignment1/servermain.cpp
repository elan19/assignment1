#include <stdio.h>
#include <stdlib.h>
/* You will to add includes here */
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdint.h>
// Included to get the support library
#include <calcLib.h>

const double ROUND_UP = 0.001;

using namespace std;

int initCalcLib(void);
int randomInt(void);
double randomFloat(void);
char* randomType(void);

int main(int argc, char *argv[]){
  
  /* Do more magic */
  
    if (argc < 2)
    {
        printf("Too few arguments\nExpected: <port>");
        exit(0);
    }

    initCalcLib();
    
    struct addrinfo guide, * serverInfo, * p;
    uint16_t numBytes;
    uint16_t sockFileD;
    uint16_t listenFileD;
    uint8_t returnValue;

    struct sockaddr_in clientAddr;
    socklen_t clientAddr_len = sizeof(clientAddr);

    char protocol[15] = "Text TCP 1.0\n";

    double fval[2];

    double result;
    double clientResult;
    char calcMsgFinal[100];

    char clientMsg[100];
    int clientMsgLen = sizeof(clientMsg);

    memset(&guide, 0, sizeof(guide));

    guide.ai_family = AF_INET;
    guide.ai_socktype = SOCK_STREAM;
    guide.ai_flags = AI_PASSIVE;

    // getaddrinfo( IP, PORT, MALL, LAGRING) != 0 (=0 om den går igenom, -1 om den misslyckas)
    if ((returnValue = getaddrinfo(NULL, argv[1], &guide, &serverInfo)) != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(returnValue));
        exit(0);
    }

    for (p = serverInfo; p != NULL; p = p->ai_next) 
    {
        if ((sockFileD = socket(p->ai_family, p->ai_socktype,
            p->ai_protocol)) == -1)
        {
            printf("listener: socket: %s\n", gai_strerror(errno));
            continue;
        }

        if (bind(sockFileD, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockFileD);
            printf("listener error: bind: %s\n", gai_strerror(errno));
            continue;
        }

        break;
    }

    if (p == NULL)
    {
        printf("Could not create socket!");
        exit(0);
    }

}
