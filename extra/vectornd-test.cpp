#include "vectornd.h"
#include "matrixnd.h"

int main(int argc, char** argv) {
    Vector<2> a(5.0, 4.0);
    Vector<3> b1(1.0, 0.0, 0.0), b2(0.0, 1.0, 0.0), b3(0.0, 0.0, 1.0);
    Vector<4> c1(0.0, 0.0, 0.0, 0.0), c2(0.0, 0.0, 0.0, 0.0);
    
    Matrix<3> m1(b1, b2, b3);
    m1 *= 2;
    
    Matrix<2, 4> m2(c1, c2);
    Matrix<4, 2> m2t = m2.Transpose();
    
    std::cout << a << "; Norm: " << a.Norm() << std::endl;
    std::cout << c1 << std::endl;
    std::cout << std::endl << "m1:\n" << m1 << std::endl << std::endl;
    std::cout << std::endl << "m2:\n" << m2 << std::endl << std::endl;
    std::cout << std::endl << "m2t:\n" << m2t << std::endl << std::endl;
    
    Vector<3> r = b1 + 2*b2 + b3;
    std::cout << "     r = " << r << std::endl;
    r = m1 * r;
    std::cout << "m1 * r = " << r << std::endl;
    
    Matrix<2, 2> p = m2 * m2t;
    std::cout << "\nm1 * m2 =\n" << p << std::endl;
    return 0;
}