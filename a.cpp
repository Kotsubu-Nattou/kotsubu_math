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

    const double Deg30 = 0.5235987755982988;
    const double Deg45 = 0.7853981633974483;
    
    // for (int i=-1; i<=1; ++i) {
    //     for (int j=-1; j<=1; ++j) {
    //         cout << math.rightTriangle.baseLen(Vec2(0,0), Vec2(j,i), Deg45) << endl;
    //     }
    // }

    cout << math.rightTriangle.height(Vec2(10,-10), Vec2(0,0), Vec2(500,0)) << endl;
    cout << math.rightTriangle.height(Vec2(10,-10), Vec2(0,0), Vec2(0,500)) << endl;
    cout << math.rightTriangle.height(Vec2(0,0), Vec2(10,-10), Vec2(500,-10)) << endl;
    cout << math.rightTriangle.height(Vec2(0,0), Vec2(10,-10), Vec2(10,500)) << endl;


    return 0;
}
