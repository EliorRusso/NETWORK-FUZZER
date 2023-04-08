
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define PORT 1337
#define BUFFER_SIZE 65535

int main(int argc, char *argv[]) {
    char buffer[BUFFER_SIZE] = "/AX/";
    int buffer_len = 1;
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_address = {0};
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    inet_pton(AF_INET, "192.168.200.37", &server_address.sin_addr);
    if(connect(sock, (struct sockaddr*)&server_address, sizeof(server_address)) == 0) {
        srand(time(0));
        while (1) {
            if(buffer_len >= BUFFER_SIZE) {
                printf("Buffer overflow detected. Exiting.\n");
                break;
            }
            printf("Fuzzing with %d bytes\n", buffer_len);
            int bytes = send(sock, buffer, buffer_len, 0);
            if(bytes < 0) {
                perror("send");
                return 1;
            }
            buffer_len+=2;
            // increase buffer size by appending random characters
            buffer[buffer_len-1] = rand() % 256;
            buffer[buffer_len-2] = '/';
        }
    } else {
        printf("Could not connect.\n");
    }
    close(sock);
    return 0;
}
