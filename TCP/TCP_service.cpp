#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>


int main(){

    int SerSocket, CliSocket;
    struct sockaddr_in SerAddr, CliAddr;

    SerSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(SerSocket == -1){
        perror("SerSocket");
        exit(0);
    }
    SerAddr.sin_family = PF_INET;
    SerAddr.sin_addr.s_addr = inet_addr("0.0.0.0");
    SerAddr.sin_port = htons(6969);

    int Bind = bind(SerSocket, (sockaddr*)& SerAddr, sizeof(SerAddr));
    if(Bind == -1){
        perror("bind");
        close(SerSocket);
        exit(0);
    }

    listen(SerSocket, 5);
    socklen_t len =  sizeof(CliAddr);
    CliSocket = accept(SerSocket, (sockaddr*)& CliAddr, &len); 
    if(CliSocket == -1){
        perror("accept");
        close(SerSocket);
        exit(0);
    }
    char SendBuff[] = {"hello TCP"};
    write(CliSocket, SendBuff, sizeof(SendBuff));
    close(CliSocket);

    return 0;
}
