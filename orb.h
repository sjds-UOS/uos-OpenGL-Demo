#ifndef ORB_H
#define ORB_H

#include <cmath>
#include "vec.h"

// 定义一个球类用于绘制，与光线求交
class orb
{
public:
    Vecf center;                      // 球心坐标位置
    float radius, radius2;            // 球半径以及半径的平方
    Vecf surfaceColor, emissionColor; // 表面颜色和传递的颜色
    float transparency, reflection;   // 表面反射率和透明度

    orb() {}
    orb(
        const Vecf &c,           // 中心点向量
        const float &r,          // 半径
        const Vecf &sc,          // 表面颜色
        const float &refl = 0,   // 折射率
        const float &transp = 0, // 反射率
        const Vecf &ec = 0) : center(c), radius(r), radius2(r * r), surfaceColor(sc), emissionColor(ec),
                              transparency(transp), reflection(refl)
    {
    }

    bool intersect(const Vecf &rayorig, // 光线原点
                   const Vecf &raydir,  // 光线方向
                   float *t0,           // 第一个交点
                   float *t1            // 第二个交点
    ) const
    {
        Vecf l = center - rayorig; // 光线原点到球心向量l
        float cos = l.dot(raydir); // 入射方向和光线到球心向量的夹角余弦,cos = l*cos夹角
        if (cos < 0)
            return false;                  // 如果夹角大于90度，光线不可能射中球体
        float d2 = l.dot(l) - (cos * cos); // d2 = l^2-l^2*cos^2 = l^2*sin^2
        if (d2 > radius2)
            return false;               // 光线和球无交点
        float thc = sqrt(radius2 - d2); // radius2 = r^2
        if (t0 != nullptr && t1 != nullptr)
        {
            *t0 = cos - thc; // 到前一个交点的距离
            *t1 = cos + thc; // 到后一个交点的距离
        }
        return true;
    }
};

#endif