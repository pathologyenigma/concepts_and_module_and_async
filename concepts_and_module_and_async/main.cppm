import <iostream>;

import types.Vec;
using namespace math;

int main(int argc, char* argv[])
{
    auto m1 = new Matrix<float, 3, 4>(1);
    auto m2 = new Matrix<float, 3 ,4>(1);
    auto m3 = *m1 + *m2;
    auto m4 = m3 - *m1;
    auto m5 = m3 * m3;
    auto m6 = m5 / m5;
    std::cout << m6 << std::endl;
    float a[12] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    auto m7 = new Matrix<float, 3, 4>(a);
    std::cout << *m7;
    delete m2;
    delete m1;
}