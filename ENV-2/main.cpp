#include <iostream>
#include <vector>
#include "complex.h"
#include "sort.h"

int main() {
    std::vector<Complex> numbers = {
        Complex(3, 4),    
        Complex(1, 1),    
        Complex(0, 5),    
        Complex(-2, -2), 
        Complex(4, 0)     
    };
    
    std::cout << "Исходный массив комплексных чисел:" << std::endl;
    for (const auto& num : numbers) {
        std::cout << num << " (модуль: " << num.abs() << ")" << std::endl;
    }
    std::cout << std::endl;
    
    Complex a(2, 3);
    Complex b(1, -1);
    
    std::cout << "Демонстрация операций:" << std::endl;
    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
    std::cout << "a + b = " << (a + b) << std::endl;
    std::cout << "a - b = " << (a - b) << std::endl;
    std::cout << "a * 2.5 = " << (a * 2.5) << std::endl;
    std::cout << "|a| = " << a.abs() << std::endl;
    std::cout << std::endl;
    
    bubbleSort(numbers);
    
    std::cout << "Отсортированный массив (по модулю):" << std::endl;
    for (const auto& num : numbers) {
        std::cout << num << " (модуль: " << num.abs() << ")" << std::endl;
    }
    
    return 0;
}
