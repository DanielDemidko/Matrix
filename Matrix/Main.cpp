#include <iostream>
#include "Matrix.h"


void Sample()
{
    size_t m, n;
    std::cout << "Enter M, N: ";
    std::cin >> m >> n;
    std::cout << "Enter matrix A " << m << 'x' << n << ':' << std::endl;
    Matrix<int> test(m, n);
    std::cin >> test;
    auto transposed = test.Transpose();
    std::cout
        << "\nA:\n" << test
        << "\nT:\n" << transposed
        << "\nA*T:\n" << test.CanMultiplied(transposed) << std::endl << test * transposed;
}


int main()
{
    Sample();
}

