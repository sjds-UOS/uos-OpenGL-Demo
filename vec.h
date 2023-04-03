#ifndef VEC_H
#define VEC_H

// 定义一个三维向量类
template <typename T>
class Vec
{
public:
    T x, y, z;
    Vec() : x(T(0)), y(T(0)), z(T(0)) {}
    Vec(T xx) : x(xx), y(xx), z(xx) {}
    Vec(T xx, T yy, T zz) : x(xx), y(yy), z(zz) {}
    Vec &normalize() // 向量的danwei1化
    {
        T nor2 = length2();
        if (nor2 > 0)
        {
            T invNor = 1 / sqrt(nor2);
            x *= invNor, y *= invNor, z *= invNor;
        }
        return *this;
    }

    // Vec中部分运算符的重载

    Vec<T> operator*(const T &f) const { return Vec<T>(x * f, y * f, z * f); }
    Vec<T> operator*(const Vec<T> &v) const { return Vec<T>(x * v.x, y * v.y, z * v.z); }
    Vec<T> operator-(const Vec<T> &v) const { return Vec<T>(x - v.x, y - v.y, z - v.z); }
    Vec<T> operator+(const Vec<T> &v) const { return Vec<T>(x + v.x, y + v.y, z + v.z); }
    T dot(const Vec<T> &v) const { return x * v.x + y * v.y + z * v.z; }

    Vec<T> &operator+=(const Vec<T> &v)
    {
        x += v.x, y += v.y, z += v.z;
        return *this;
    }
    Vec<T> &operator*=(const Vec<T> &v)
    {
        x *= v.x, y *= v.y, z *= v.z;
        return *this;
    }
    Vec<T> operator-() const { return Vec<T>(-x, -y, -z); }
    T length2() const { return x * x + y * y + z * z; } // 获取到原点位置平方数据
    T length() const { return sqrt(length2()); }
    friend std::ostream &operator<<(std::ostream &os, const Vec<T> &v)
    {
        os << "[" << v.x << " " << v.y << " " << v.z << "]";
        return os;
    }
};

typedef Vec<float> Vecf;

#endif