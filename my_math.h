/**********************************************************************************************
【ヘッダオンリークラス】my_math

・概要
  数学で使う定数とメソッドを集めたシングルトン。
  一部のメソッド、および全ての定数はstaticなので、インクルードだけで利用可能。
  基本的にベクトルは、OpenSiv3DのVec2で運用することを前提とした。
  もし、クラスstruct_vecのVEC2を使う場合は、このファイル冒頭、または
  このファイルをインクルードする前に、"USE_STRUCT_VEC"をdefineしておく。

・利用例
  #include "MyMath.h"
  n = MyMath::Pi;                        // 定数はインクルードするだけで利用可能
  MyMath &math = MyMath::getInstance();  // 唯一のインスタンスを取得。初めての場合、
                                         // 数学用テーブルが初期化され利用可能となる。
  n = math.direction(v);                 // 通常の定数、メソッドの利用例
***********************************************************************************************/

#pragma once

// @ Vec2の定義
// クラスstruct_vecのVEC2を利用する場合はコメントを外す。
//#define USE_STRUCT_VEC

#include <cmath>
#ifdef USE_STRUCT_VEC
    #include "struct_vec.h"
#else
    #include <Siv3D.hpp>
#endif





///////////////////////////////////////////////////////////////////////////////////////////////
// 【クラス】MyMath
//
class MyMath {

#ifdef USE_STRUCT_VEC
    using Vec2 = VEC2<double>;  // クラスstruct_vecのVEC2
#endif
    


public:
    // 【定数】数学用の定数
    static constexpr double Epsilon    = 0.00001;           // これ未満を0とする値
    static constexpr double Pi         = 3.141592653589793; // π
    static constexpr double TwoPi      = Pi * 2.0;          // Radianの最大値
    static constexpr double RightAngle = Pi / 2.0;          // 直角（90°）のRadian
    static constexpr double Deg2Rad    = Pi / 180.0;        // Degに掛けるとRad
    static constexpr double Rad2Deg    = 180.0 / Pi;        // Radに掛けるとDeg
    static constexpr double RootTwo    = 1.414213562373095; // 斜辺が45°の直角三角形における、斜辺の比（他の辺は共に1）
    static constexpr double RoundFix   = 0.5;               // これを正の小数に足して整数にすると四捨五入
    static constexpr double One        = 1.0;               // double 1.0
    static constexpr double Two        = 2.0;               // double 2.0
    static constexpr double Half       = 0.5;               // double 0.5



    // 【メソッド】sin（テーブル引き）
    double sin(double radian)
    {
        int id = abs(static_cast<int>(radian * Sin.Resolution)) % Sin.ScaledTwoPi;

        if (id < Sin.TableMax)
            return (radian < 0.0) ? -Sin.table[id] :  Sin.table[id];
        else {
            id -= Sin.TableMax;
            return (radian < 0.0) ?  Sin.table[id] : -Sin.table[id];
        }
    }



    // 【メソッド】cos（テーブル引き）
    double cos(double radian)
    {
        return sin(radian + RightAngle);
    }



    // 【メソッド】asin（テーブル引き）
    double asin(double ratio)
    {
        int id = abs(static_cast<int>(ratio * ratio * Asin.TableMax + RoundFix));
        if (id >= Asin.TableMax) id = Asin.TableMax - 1;

        return (ratio < 0.0) ? -Asin.table[id] : Asin.table[id];
    }



    // 【メソッド】acos（テーブル引き）
    double acos(double ratio)
    {
        return RightAngle - asin(ratio);
    }



    // 【メソッド】ベクトルの長さを返す
    static double length(Vec2 v)
    {
        return sqrt(lengthPow(v));
    }



    // 【メソッド】ベクトルの長さを返す（ルートを取らない）
    static double lengthPow(Vec2 v)
    {
        return v.x * v.x + v.y * v.y;
    }



    // 【メソッド】2点間の距離を返す
    static double distance(Vec2 a, Vec2 b)
    {
        return sqrt(distancePow(a, b));
    }



    // 【メソッド】2点間の距離を返す（ルートを取らない）
    static double distancePow(Vec2 a, Vec2 b)
    {
        Vec2 v(a - b);
        return v.x * v.x + v.y * v.y;
    }



    // 【メソッド】ベクトルを正規化して返す
    static Vec2 normalize(Vec2 v)
    {
        double len = length(v);
        if (len < Epsilon) return v;

        len = One / len;
        return v *= len;
    }



    // 【メソッド】内積を返す
    static double innerProduct(Vec2 a, Vec2 b)
    {
        return a.x * b.x + a.y * b.y;
    }



    // 【メソッド】内積を返す（aとスクリーンx）
    static double innerProduct(Vec2 a)
    {
        // 基準の軸は、成分x=1,y=0なので、数式がとても簡単
        // return a.x * 1.0 + a.y * 0.0;
        return a.x;
    }



    // 【メソッド】外積を返す
    static double outerProduct(Vec2 a, Vec2 b)
    {
        return a.x * b.y - b.x * a.y;
    }



    // 【メソッド】外積を返す（aとスクリーンx）
    static double outerProduct(Vec2 a)
    {
        // 基準の軸は、成分x=1,y=0なので、数式がとても簡単
        // return a.x * 0.0 - 1.0 * a.y;
        // return 0.0 - a.y;
        return -a.y;
    }



    // 【メソッド】ベクトルの向きを返す（スクリーン座標系。atan2の代わりに使えて高速）
    // ＜戻り値＞ -180°から180°のradian
    double direction(Vec2 v)
    {
        return direction(v.x, v.y);
    }



    // 【メソッド】ベクトルの向きを返す（スクリーン座標系。atan2の代わりに使えて高速）
    // ＜戻り値＞ -180°から180°のradian
    double direction(double vx, double vy)
    {
        double len = sqrt(vx * vx + vy * vy);
        if (len < Epsilon) return 0.0;

        // 基準の軸は、成分x=1,y=0なので、数式がとても簡単
        double cosVal = vx / len;  // 「内積/長さ」で余弦値を求める
        return (vy < 0.0) ? -acos(cosVal) : acos(cosVal);  // 外積を見て、360度角を得る
    }



    // 【メソッド】2ベクトル間の角度を返す
    // ＜戻り値＞ -180°から180°のradian
    double angle(Vec2 a, Vec2 b)
    {
        return fmod(direction(b) - direction(a), TwoPi);
    }



    // 【メソッド】ベクトルを回転して返す
    Vec2 rotation(Vec2 v, double radian)
    {
        return rotation(v, sin(radian), cos(radian));
    }



    // 【メソッド】ベクトルを回転して返す
    static Vec2 rotation(Vec2 v, double sinVal, double cosVal)
    {
        return { v.x * cosVal - v.y * sinVal,
                 v.x * sinVal + v.y * cosVal };
    }



    // 【メソッド】唯一のインスタンスを返す
    // なるべく計算のロジックに近い所で受け取るようにすると、キャッシュが効くためか高速化する
    static MyMath& getInstance()
    {
        static MyMath inst;
        return inst;
    }





private:
    // @@@ テーブル構造体
    struct SinTable
    {
        static constexpr int Resolution  = 2000;
        static constexpr int TableMax    = static_cast<int>(Pi * Resolution);
        static constexpr int ScaledTwoPi = static_cast<int>(TwoPi * Resolution);
        double table[TableMax];
    } Sin;

    struct AsinTable
    {
        static constexpr int Resolution  = 3000;
        static constexpr int TableMax    = Resolution;
        double table[TableMax];
    } Asin;



    // @@@ 隠しメソッド
    MyMath()  // 隠しコンストラクタ
    {
        // sinテーブルを作成（cos兼用）
        double n;
        for (int i = 0; i < Sin.TableMax; ++i) {
            n = std::sin(static_cast<double>(i) / Sin.Resolution);
            Sin.table[i] = (n < Epsilon) ? 0.0 : n;
        }
        
        // asinテーブルを作成（acos兼用）
        double max = Asin.TableMax - 1;
        for (int i = 0; i < Asin.TableMax; ++i) {
            n = std::asin(sqrt(i / max));
            Asin.table[i] = (n < Epsilon) ? 0.0 : n;
        }
    }
    ~MyMath(){}                        // 隠しデストラクタ
    MyMath(const MyMath&);             // 隠しコピーコンストラクタ
    MyMath& operator=(const MyMath&);  // 隠しコピー代入演算子
};
