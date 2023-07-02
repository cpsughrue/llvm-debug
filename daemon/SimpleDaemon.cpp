#include <unistd.h>
#include <signal.h>
#include <sys/stat.h>
#include <iostream>

void handle_signal(int signal) {
    std::cout << "Received signal " << signal << ", terminating...\n";
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

    sleep(20);

    return EXIT_SUCCESS;
}
