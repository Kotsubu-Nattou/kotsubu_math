#include <iostream>
#include <cmath>
#include "kotsubu_vec.h"
#define USE_KOTSUBU_VEC
#include "kotsubu_math.h"
using namespace std;



// kotsubu_mathのテストプログラム
int main()
{
    KotsubuMath& math = KotsubuMath::getInstance();
    VEC2<double> a(0, 0), b(10, 10);


    cout << "Distance : " << math.distance(a, b) << endl;
    cout << "Direction: " << math.angle(a, b) << endl;


    return 0;
}
