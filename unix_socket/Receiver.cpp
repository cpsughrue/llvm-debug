#include <sys/socket.h>
#include <sys/un.h>
#include <string>
#include <iostream>
#include <unistd.h>

#define MAX_BUFFER 1024

int main() {
    struct sockaddr_un addr;
    int fd, client;

    // new socket
    if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        std::perror("socket error");
        return -1;
    }

    // set addr to all 0s
    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, "/tmp/DaemonSocket", sizeof(addr.sun_path)-1);
    
    // delete socket file if it exists
    unlink("/tmp/DaemonSocket");

    // bind to local address
    if (bind(fd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
        std::perror("bind error");
        return -1;
    }

    // marks socket refered to by fd as passive (used to accept incoming connection request)
    if (listen(fd, 5) == -1) {
        std::perror("listen error");
        return -1;
    }

    while (true) {

        // receive incoming connection
        // creates new socket
        // does not impact listening socket
        if ((client = accept(fd, NULL, NULL)) == -1) {
            std::perror("accept error");
            continue;
        }

        char buf[MAX_BUFFER];
        memset(buf, 0, MAX_BUFFER);

        // read MAX_BUFFER bytes from cl to buf
        int n = read(client, buf, MAX_BUFFER);

        if (n <= 0) {
            if (n < 0) perror("read error");
            else fprintf(stderr, "EOF\n");
        } else {
            printf("Received: %s\n", buf);
        }

        close(client);
    }

    return 0;
}
