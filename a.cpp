#include <iostream>
#include <cmath>
#include "kotsubu_vec.h"
#define USE_KOTSUBU_VEC
#include "kotsubu_math.h"
using namespace std;
using Vec2 = VEC2<double>;


// kotsubu_mathのテストプログラム
int main()
{
    KotsubuMath& math = KotsubuMath::getInstance();


    cout << math.rightTriangle.height(Vec2(10,0), Vec2(0,0), 0.523) << endl;


    return 0;
}
