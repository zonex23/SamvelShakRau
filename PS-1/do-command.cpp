#include <unistd.h>
#include <sys/wait.h>
#include <chrono>
#include <iostream>

int main(int argc, char** argv) {
    if (argc < 2) return 1;

    auto start = std::chrono::steady_clock::now();

    pid_t pid = fork();
    if (pid == 0) {
        execvp(argv[1], argv + 1);
        return 1;
    }

    int status;
    waitpid(pid, &status, 0);

    auto end = std::chrono::steady_clock::now();
    double seconds = std::chrono::duration<double>(end - start).count();

    std::cout << "Command completed with " << WEXITSTATUS(status)
              << " exit code and took " << seconds << " seconds.\n";

    return 0;
}
