#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <vector>
#include <sys/epoll.h>

struct s_info
{
    struct sockaddr_in cli_addr;
    int conn_fd;
};

#ifdef false
void *worker(void *arg)
{
    s_info *info = (s_info *)arg;
    int con_fd = info->conn_fd;
    sockaddr_in cli_addr = info->cli_addr;
    printf("new thread, client addr:%s, port:%d\n", inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));
    char buffer[1024];
    while (true)
    {
        memset(buffer, 0, sizeof(buffer));
        sprintf(buffer, "I'm server, I'm ready.");
        int w_ft;
        // 发送
        if ((w_ft = write(con_fd, buffer, sizeof(buffer))) < 0)
        {
            printf("write error:%s\n", strerror(errno));
            exit(1);
        }

        memset(buffer, 0, sizeof(buffer));
        // 接受
        int r_ft = read(con_fd, buffer, sizeof(buffer));
        if (r_ft == 0)
        {
            printf("client close\n");
            break;
        }
        else
        {
            printf("read:%s\n", buffer);
        }
    }
    return 0;
}

int main()
{
    struct sockaddr_in svc_addr, cli_addr;
    socklen_t cli_len = sizeof(cli_addr);
    int svc_fd, con_fd;
    
    svc_fd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&svc_addr, 0, sizeof(svc_addr));
    svc_addr.sin_family = AF_INET;
    svc_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    svc_addr.sin_port = htons(8000);
    if (bind(svc_fd, (sockaddr *)&svc_addr, sizeof(svc_addr)) < 0)
    {
        perror("bind error");
        exit(1);
    }

    if (listen(svc_fd, 2048) < 0)
    {
        perror("listen error");
        exit(1);
    }

    while (true)
    {
        memset(&cli_addr, 0, sizeof(cli_addr));
        if ((con_fd = accept(svc_fd, (sockaddr *)&cli_addr, &cli_len)) < 0)
        {
            printf("accept error:%s\n", strerror(errno));
            exit(1);
        }
        printf("accept a client, addr:%s, port:%d\n", inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));
        
        s_info info = {cli_addr, con_fd};
        pthread_t tid = 0;
        pthread_create(&tid, NULL, worker, (void *)&info);
    }
    return 0;
}

#endif

#include <deque>
#include <memory>

struct SpawnEntityInfo
{
    int32_t spawn_type = 1;
    ~SpawnEntityInfo()
    {
        // printf("SpawnEntityInfo dtor\n");
    }
    char data[1024];
};

struct SpawnerAddEntityInfo : public SpawnEntityInfo
{
    ~SpawnerAddEntityInfo()
    {
        printf("SpawnerAddEntityInfo dtor\n");
    }
    char data[102400];
};

struct SpawnerDelEntityInfo : public SpawnEntityInfo
{
    ~SpawnerDelEntityInfo()
    {
        printf("SpawnerDelEntityInfo dtor\n");
    }
    char data[1024];
};

#include <iostream>
#include <unordered_map>

int main()
{
    sleep(3);
    std::deque<uint64_t> a;
    while (true)
    {
        a.push_back(1);
        a.pop_front();
    }
    
}