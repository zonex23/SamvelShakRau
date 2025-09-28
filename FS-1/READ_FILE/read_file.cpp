#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    if (argc < 2){
        std::cout << "File path is not provided" << std::endl;
        return 1;
    }

    const char* path = argv[1];
    int fd = open(path, O_RDONLY);
    if (fd == -1){  
        perror("Error while opening the file");
        exit(EXIT_FAILURE);  
    }

    const size_t buff_size = 100;
    char buffer[buff_size + 1];

    ssize_t isRead = read(fd, buffer, buff_size);
    if (isRead == -1){
        perror("Error while reading the file");
        exit(EXIT_FAILURE);
    }
    
    buffer[isRead] = '\0';
    std::cout << buffer << std::endl;

    close(fd);
    return 0;
}
