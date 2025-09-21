#include "complex.h"

Complex::Complex() : real(0.0), imag(0.0) {}

Complex::Complex(double r, double i) : real(r), imag(i) {}

double Complex::getReal() const { return real; }
double Complex::getImag() const { return imag; }

void Complex::setReal(double r) { real = r; }
void Complex::setImag(double i) { imag = i; }

Complex Complex::operator+(const Complex& other) const {
    return Complex(real + other.real, imag + other.imag);
}

Complex Complex::operator-(const Complex& other) const {
    return Complex(real - other.real, imag - other.imag);
}

Complex Complex::operator*(double scalar) const {
    return Complex(real * scalar, imag * scalar);
}

double Complex::abs() const {
    return std::sqrt(real * real + imag * imag);
}

bool Complex::operator<(const Complex& other) const {
    return this->abs() < other.abs();
}

bool Complex::operator>(const Complex& other) const {
    return this->abs() > other.abs();
}

std::ostream& operator<<(std::ostream& os, const Complex& c) {
    os << c.real;
    if (c.imag >= 0) {
        os << " + " << c.imag << "i";
    } else {
        os << " - " << -c.imag << "i";
    }
    return os;
}
