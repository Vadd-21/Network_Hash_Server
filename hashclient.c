// requirres 3 to 4 arguments
// example input
// hashclient 1234 md5 127.0.0.1 file.1 file.2
// hashclient md5 127.0.0.1 file.1
#include "hashclient.h"

int checkHashType(char *hashType)
{
    return 1;
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

int sendLoop(int socket, char *file, int hash)
{
    /*
    send int hash, int sizeof file
    send file
    recv int len
    char *buffer = malloc(sizeof(char) *len)
    revc char* hash output
    printf hash output, filename
    free(buffer)
    */
    union initialPayload data;
    data.hash = hash;
    data.sz = 15;
    printf("data is %c, thats it\n", data.data[0]);
    return 0;
}

int main(int argc, char *argv[])
{
    int ret = 0;
    int port = 0;
    int ittrStart = 1;
    int mysocket; /* socket used to listen for incoming connections */
    int hashSelection = 0;
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
        printf("too few arguments provided\n");
        ret = -1;
        goto end;
    }
    port = checkPort(argv[1]);
    if(port == 0) //if an invalid port is provided, this will default to 1234
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
        printf("invalid hash type requested\n");
        ret = -2;
        goto end;
    }
    
    strncpy(IPAddr, argv[ittrStart++], 16);
    dest.sin_addr.s_addr = inet_addr(IPAddr); /* set destination IP number - localhost, 127.0.0.1*/ 
    if(dest.sin_addr.s_addr == -1) //checks the provided IP address is valid, possible chance of issue if 255.255.255.255 is provided
    {
        printf("invalid IP address provided\n");
        ret = -3;
        goto end; 
    }
    
    connect(mysocket, (struct sockaddr *)&dest, sizeof(struct sockaddr_in));
    for (int i = ittrStart; i < argc; i++)
    {
        sendLoop(mysocket, argv[i], hashSelection);
        printf("%s\n", argv[i]);
    }
    
end:
    free(hashType);
    free(IPAddr);
    return ret;
}

/*
md5
sha1
sha224
sha256
sha384
sha512
shake_128
shake_256
blake2b
*/