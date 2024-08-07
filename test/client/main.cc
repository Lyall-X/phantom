#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef false
int main()
{
    struct sockaddr_in svc_adr;
    int cli_fd, con_fd;
    
    if ((cli_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("fd error");
        exit(1);
    }
    
    memset(&svc_adr, 0, sizeof(svc_adr));
    svc_adr.sin_addr.s_addr = inet_addr("127.0.0.1");
    svc_adr.sin_port = htons(8000);
    svc_adr.sin_family = AF_INET;

    if ((con_fd = connect(cli_fd, (sockaddr *)&svc_adr, sizeof(svc_adr))) < 0)
    {
        perror("connect error");
        exit(1);
    }   

    while(true)
    {
        char buf[1024];
        memset(buf, 0, sizeof(buf));
        scanf("%s", buf);
        write(cli_fd, buf, strlen(buf));       
    }

    return 0;
}
#endif

int main()
{
    struct sockaddr_in svc_adr;
    int cli_fd;
    
    cli_fd = socket(AF_INET, SOCK_DGRAM, 0);
    
    memset(&svc_adr, 0, sizeof(svc_adr));
    svc_adr.sin_family = AF_INET;
    svc_adr.sin_addr.s_addr = inet_addr("127.0.0.1");
    svc_adr.sin_port = htons(8000);

    while(true)
    {
        char buf[1024];
        memset(buf, 0, sizeof(buf));
        scanf("%s", buf);
        sendto(cli_fd, buf, strlen(buf), 0, (sockaddr *)&svc_adr, sizeof(svc_adr));
    }
}