#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
/*
Refrences
https://en.wikibooks.org/wiki/C_Programming/Networking_in_UNIX

*/

union initialPayload
{
    struct
    {
        int hash;
        long sz;
    };
    char data[sizeof(int)*2];
};
