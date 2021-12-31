import <iostream>;

import math.Vec;
import math.Matrix;
using namespace math;

int main(int argc, char* argv[])
{
    double a[3] = { 1.0, 2.0, 3.0 };
    auto v1 = new Vec3(a);
    auto v2 = new Vec3(11);
    auto v3 = (*v2).unit_vec();
    std::cout << v3 << *v2;
}