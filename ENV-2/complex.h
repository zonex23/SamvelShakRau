#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>
#include <cmath>

class Complex {
private:
    double real;
    double imag;

public:
    Complex();
    Complex(double r, double i);
    
    double getReal() const;
    double getImag() const;
    void setReal(double r);
    void setImag(double i);
    
    // Базовые операции
    Complex operator+(const Complex& other) const;
    Complex operator-(const Complex& other) const;
    Complex operator*(double scalar) const;
    
    double abs() const;
   
    bool operator<(const Complex& other) const;
    bool operator>(const Complex& other) const;
    
    friend std::ostream& operator<<(std::ostream& os, const Complex& c);
};

#endf
