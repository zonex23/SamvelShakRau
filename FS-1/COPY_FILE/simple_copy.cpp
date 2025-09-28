#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <cstdlib>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "Error while providing the paths"<< std::endl;
        exit(EXIT_FAILURE);
    }

    const char* sourcePath = argv[1];
    const char* destPath = argv[2];

    int sourceFd = open(sourcePath, O_RDONLY);
    if (sourceFd == -1) {
        perror("Error opening source file");
        exit(EXIT_FAILURE);
    }

    int destFd = open(destPath, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (destFd == -1) {
        perror("Error opening destination file");
        close(sourceFd);
        exit(EXIT_FAILURE);
    }

    const size_t bufferSize = 1024;
    char buffer[bufferSize];
    ssize_t bytesRead;

    bytesRead = read(sourceFd, buffer, bufferSize))
    ssize_t bytesWritten = write(destFd, buffer, bytesRead);
    if (bytesWritten != bytesRead) {
        perror("Error writing to destination file");
        close(sourceFd);
        close(destFd);
        exit(EXIT_FAILURE);
        }

    if (bytesRead == -1) {
        perror("Error reading from source file");
        close(sourceFd);
        close(destFd);
        exit(EXIT_FAILURE);
    }

    close(sourceFd);
    close(destFd);
    
    return 0;
}
