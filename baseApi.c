#include <unistd.h>
#include <stdio.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>

#define HOSTLEN    256

int main() {
    char hostname[HOSTLEN];

    gethostname( hostname, HOSTLEN );     // 获取主机名
    printf( "%s\n", hostname );           // ==> ubuntu

    /*
        struct hostent {
            char *h_name;         // 官方域名，字符串
            char **h_aliases;     // 其他域名，字符串数组
            int  h_addrtype;      // 保存在h_addr_list的IP地址的地址族信息，AF_INET为IPv4
            int  h_length;        // IP地址长度
            char **h_addr_list;   // 以整数形式保存域名对应的IP地址
        };
    */
    // 根据主机名返回hostent结构体地址或NULL指针
    struct hostent *hp = gethostbyname( /*"www.baidu.com"*/ hostname );
    if ( hp ) {
        printf( "official hostname: %s\n", hp->h_name );
        // 处理char**
        for ( char **pptr = hp->h_aliases; *pptr != NULL; pptr++ )
            printf("alias: %s\n", *pptr);
        switch ( hp->h_addrtype ) {
            case AF_INET:
                printf("address type: ip-v4\n");
                break;
            case AF_INET6:
                printf("address type: ip-v6\n");
                break;
            default:
                break;
        }
        char str[128];
        struct sockaddr_in addr;
        for ( char **pptr = hp->h_addr_list; *pptr != NULL; pptr++ ) {
            printf( "ip address: %s\n", inet_ntop(hp->h_addrtype, *pptr, str, sizeof(str)) );
            bcopy( (void*)*pptr, (void*)&(addr.sin_addr), hp->h_length );
            printf( "ip address2: %s\n",  inet_ntoa(addr.sin_addr) );
        }
    }

}