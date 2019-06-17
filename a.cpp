#include <iostream>
#include <cmath>
#include "struct_vec.h"
#define USE_STRUCT_VEC
#include "my_math.h"
namespace
{
    const double Pi    = 3.141592653589793;
    const double TwoPi = Pi * 2.0;            // Radianの最大値
}
using namespace std;



// クラスmy_mathのテストプログラム
int main()
{
    MyMath math;

    // for (int i=-14; i<=14; ++i) {
    //     double rad = TwoPi * i / 12;
    //     printf("rad[%3.2f]   sin: %8f,   Sin: %8f\n", rad,  sin(rad), math.sin(rad));
    //     // printf("rad[%3.2f]   cos: %8f,   Cos: %8f\n", rad,  cos(rad), math.cos(rad));
    // }

    // for (double ratio = -1.3; ratio < 1.3; ratio += 0.1) {
    //     // printf("ratio[%3.2f]   asin:%8f,   acos:%8f\n", ratio, std::asin(ratio), std::acos(ratio));
    //     printf("ratio[%3.2f]   asin: %8f,   Asin: %8f\n", ratio, std::asin(ratio), math.asin(ratio));
    //     // printf("ratio[%3.2f]   acos: %8f,   Acos: %8f\n", ratio, std::acos(ratio), math.acos(ratio));
    // }


    return 0;
}

