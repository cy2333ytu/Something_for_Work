/*
TCP通信 客户端

*/
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>


int main(){
    int CliSocket;
    struct sockaddr_in SerAddr;

    CliSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(CliSocket == -1){
        perror("CliSocket");
        exit(0);
    }
    SerAddr.sin_family = PF_INET;
    SerAddr.sin_addr.s_addr = inet_addr("192.168.254.162");
    SerAddr.sin_port = htons(6969);

    connect(CliSocket, (sockaddr*)& SerAddr, sizeof(SerAddr));

    char buf[100] = {};
    read(CliSocket, buf, sizeof(buf));
    printf("%s\r\n", buf);

    close(CliSocket);

    return 0;
}