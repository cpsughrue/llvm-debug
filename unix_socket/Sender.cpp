#include <sys/socket.h>
#include <sys/un.h>
#include <string>
#include <iostream>
#include <unistd.h>

int main() {
    struct sockaddr_un addr;
    int fd;

    // new socket
    if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        std::perror("socket error");
        return -1;
    }

    // set addr to all 0s
    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, "/tmp/DaemonSocket", sizeof(addr.sun_path)-1);

    // connect to remote address
    if (connect(fd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
        std::perror("connect error");
        return -1;
    }

    // write
    std::string message = "Hello, Receiver!";
    if (write(fd, message.c_str(), message.size()) != message.size()) {
        std::perror("write error");
        return -1;
    }

    close(fd);
    return 0;
}
