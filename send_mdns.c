#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <linux/if_ether.h>
#include <errno.h>
#include <string.h>
int main()
{
    int fd, ret;
    struct sockaddr_in in;
    char buf[] = {
        0x33, 0x33, 0x00, 0x00, 0x00, 0xfb, 0x00, 0x0f, 0x00, 0x67, 0x38, 0xb1, 0x81, 0x00, 0x00, 0x0a,
        0x86, 0xdd, 0x60, 0x0e, 0xa2, 0x9a, 0x00, 0x29, 0x11, 0xff, 0xfe, 0x80, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x27, 0x13, 0xcd, 0x37, 0xf9, 0xbc, 0xd5, 0x3c, 0xff, 0x02, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfb, 0x14, 0xe9, 0x14, 0xe9, 0x00, 0x29,
        0x93, 0x0d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x5f,
        0x66, 0x74, 0x70, 0x04, 0x5f, 0x74, 0x63, 0x70, 0x05, 0x6c, 0x6f, 0x63, 0x61, 0x6c, 0x00, 0x00,
        0x0c, 0x00, 0x01};

    fd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if (fd < 0)
    {
        printf("%s\n", strerror(errno));
    }

    bzero(&in, sizeof(in));
    in.sin_family = PF_PACKET;
    in.sin_addr.s_addr = inet_addr("192.168.2.11");

    ret = bind(fd, (void *)&in, sizeof(in));
    if (ret < 0)
    {
        printf("%s\n", strerror(errno));
    }
    while (1)
    {
        ret = send(fd, buf, sizeof(buf), 0);
        if (ret < 0)
        {
            printf("%s\n", strerror(errno));
            break;
        }
    }
    
}