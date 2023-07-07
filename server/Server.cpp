#include <unistd.h>
#include <signal.h>
#include <sys/stat.h>
#include <iostream>

#include <sys/socket.h>
#include <sys/un.h>
#include <string>

#define MAX_BUFFER 1024

int Server() {

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
            printf("Received: \"%s\"\n", buf);
            fflush(stdout);
        }
        close(client);
    }
    return 0;
}

void handle_signal(int signal) {
    std::cout << "Received signal " << signal << ", terminating..." << std::endl;
    exit(0);
}

int main() {

    // fork off the parent process
    pid_t pid, sid;
    pid = fork();

    if (pid < 0) {
        exit(EXIT_FAILURE);
    }
    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }

    // below code is only executed by daemon (child process)

    // change file mode mask
    // dictates the default permission setting for any new file or directory that the daemon creates
    umask(0);
            
    // Create a new SID for the child process
    // every process is part of a session
    // detaching daemon from the origional sessions
    sid = setsid();
    if (sid < 0) {
        exit(EXIT_FAILURE);
    }
    
    // Close out the standard file descriptors
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    // Handle signals
    signal(SIGTERM, handle_signal);

    // Open log file in append mode.
    freopen("daemon.log", "a", stdout);
    freopen("daemon.log", "a", stderr);

    std::cout << "daemon initialization complete" << std::endl;

    Server();

    return EXIT_SUCCESS;
}