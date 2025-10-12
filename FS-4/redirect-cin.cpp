#include <iostream>
#include <fstream>
#include <unistd.h>
#include <fcntl.h>

void initialize(int argc, char** argv)
{
    if (argc != 2) {
        std::"Eror with proveded path";
        exit(1);
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        std::cerr << " Cant open thw file '" << argv[1] <<std::endl;
        exit(1);
    }

    if (dup2(fd, STDIN_FILENO) < 0) {
        std::cerr << "Error: Failed to redirect stdin\n";
        close(fd);
        exit(1);
    }

    close(fd);
}

int main(int argc, char** argv)
{
    initialize(argc, argv);

    std::string input;
    std::cin >> input;

    std::string reversed(input.rbegin(), input.rend());

    std::cout << reversed << std::endl;

    return 0;
}
