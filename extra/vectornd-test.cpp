#include "vectornd.h"
#include "matrixnd.h"

int main(int argc, char** argv) {
    Vector<2> a(5.0, 4.0);
    Vector<3> b1(1.0, 0.0, 0.0), b2(0.0, 1.0, 0.0), b3(0.0, 0.0, 1.0);
    Vector<4> c(a);
    
    Matrix<3> m(b1, b2, b3);
    m *= 2;
    
    std::cout << a << "; Norm: " << a.Norm() << std::endl;
    std::cout << c << std::endl;
    std::cout << std::endl << "m:\n" << m << std::endl << std::endl;
    
    Vector<3> r = b1 + 2*b2 + b3;
    std::cout << "    r = " << r << std::endl;
    r = m * r;
    std::cout << "m * r = " << r << std::endl;
    return 0;
}