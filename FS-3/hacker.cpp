#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    if (argc != 2) return 1;

    int fd = open(argv[1], O_RDWR);
    if (fd < 0) return 1;

    char zero = '\0';
    char tmp;
    while (read(fd, &tmp, 1) == 1) {
        lseek(fd, -1, SEEK_CUR);
        write(fd, &zero, 1);
    }

    close(fd);
    unlink(argv[1]);
    return 0;
}
