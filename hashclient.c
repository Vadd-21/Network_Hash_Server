// requirres 3 to 4 arguments
// example input
// hashclient 1234 md5 127.0.0.1 file.1 file.2
// hashclient md5 127.0.0.1 file.1
#include "hashclient.h"

itn checkHashType(char *hashType)
{
    return 0;
}

int checkPort(char *arg)
{
    int i = atoi(arg);
    if(i)
    {
        return i;
    }
    return 0;
}

int main(int argc, char *argv[])
{
    int port = 0;
    int ittrStart = 1;
    int mysocket;            /* socket used to listen for incoming connections */
    char* hashType = malloc(10*sizeof(char));
    memset(hashType, 0, 10); // zero the memory for hashType
    char* IPAddr = malloc(16*sizeof(char)); // 15 characters is the max for an IP address considering 4 octets and 3 dots, the 16th is to hold the null terminator
    memset(IPAddr, 0, 16); // zero the memory for IPAddr
    struct sockaddr_in dest; 
    mysocket = socket(AF_INET, SOCK_STREAM, 0);
    memset(&dest, 0, sizeof(dest)); /* zero the struct */
    dest.sin_family = AF_INET;
    if(argc < 3)
    {
        goto end;
    }
    port = checkPort(argv[1]);
    if(port == 0)
    {
        port = 1234;
    }
    else
    {
        ittrStart++;
    }
    dest.sin_port = htons(port); /* set destination port number */
    strncpy(hashType, argv[ittrStart++], 10);
    if(checkHashType == 0)
    {
        goto end;
    }
    strncpy(IPAddr, argv[ittrStart++], 16);
    dest.sin_addr.s_addr = inet_addr(IPAddr); /* set destination IP number - localhost, 127.0.0.1*/ 
    connect(mysocket, (struct sockaddr *)&dest, sizeof(struct sockaddr_in));
    for (int i = ittrStart; i < argc; i++)
    {
        printf("%s\n", argv[i]);
    }
end:
    free(hashType);
    free(IPAddr);
}