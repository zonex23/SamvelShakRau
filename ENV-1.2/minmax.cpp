#include <iostream>
#include <cstdlib>

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cout << argv[0]<< std::endl;
        return 1;
    }

    int a = std::atoi(argv[1]);
    int b = std::atoi(argv[2]);
    int c = std::atoi(argv[3]);

    int min_val = a;
    if (b < min_val) min_val = b;
    if (c < min_val) min_val = c;

    int max_val = a;
    if (b > max_val) max_val = b;
    if (c > max_val) max_val = c;

    std::cout << "min-" << min_val << ", max-" << max_val << std::endl;

    return 0;
}
