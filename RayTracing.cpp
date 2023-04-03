#include "glad/glad.h"
#include <sstream>
#include <vector>
#include <iostream>
#include <cmath>
#include <fstream>
#include <algorithm>
#include <GLFW/glfw3.h>
#include "shader.h"
using namespace std;

GLuint VBO, VAO;
const GLuint WIDTH = 1200, HEIGHT = 800;

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
    T dot(const Vec<T> &v) const { return x * v.x + y * v.y + z * v.z; }
    Vec<T> operator-(const Vec<T> &v) const { return Vec<T>(x - v.x, y - v.y, z - v.z); }
    Vec<T> operator+(const Vec<T> &v) const { return Vec<T>(x + v.x, y + v.y, z + v.z); }
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

// 定义一个球类用于绘制，与光线求交
class orb
{
public:
    Vecf center;                      // 球心坐标位置
    float radius, radius2;            // 球半径以及半径的平方
    Vecf surfaceColor, emissionColor; // 表面颜色和传递的颜色
    float transparency, reflection;   // 表面反射率和透明度

    /*orb* left = NULL;
    orb* right = NULL;*/

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

// 此变量控制最大递归深度
#define MAX_RAY_DEPTH 10

float mix(const float &a, const float &b, const float &mix)
{
    return b * mix + a * (1 - mix);
}

// 这是主跟踪函数。它以光线作为参数（用原点和方向的方式表示光线）
// 测试该光线是否与场景中的任何几何体相交
// 如果光线与一个物体相交，计算交点，在交点处的法线，并对该点进行着色。
// 着色取决于曲面特性（是否透明、反射、漫反射）
// 光线不交于物体的话返回背景色
Vecf trace(
    const Vecf &rayorig,            // 光线原点
    const Vecf &raydir,             // 光线的单位方向向量
    const std::vector<orb *> &orbs, // 球体集合
    const int &depth)               // 递归深度
{
    float tnear = INFINITY;   // 一开始定义初始距离为无穷
    const orb *orb = nullptr; // 此处相当于temp

    // 在场景中找到此光线与球体最前面的交点
    for (auto i : orbs) // 对每一个球体进行相交判断
    {
        float t0 = INFINITY, t1 = INFINITY;          // 直线与球面要么两个交点，要么没有交点
        if (i->intersect(rayorig, raydir, &t0, &t1)) // 进行光线与球体的相交判断
        {
            if (t0 < 0)
                t0 = t1; // 如果光线在球的里面，就采用前面的交点

            if (t0 < tnear)
            {
                // 判断 tnear 是否是最近的交点
                tnear = t0; // 将最近的交点设置为t0
                orb = i;    // 设置球体
            }
        }
    }

    if (orb != NULL)
    {
        Vecf surfaceColor = 1.0;              // 球体表面的颜色
        Vecf phit = rayorig + raydir * tnear; // 通过光线原点+t*单位方向向量获得交点
        Vecf nhit = phit - orb->center;       // 计算交点法向量
        nhit.normalize();                     // 交点法向量规范化
        float bias = 1e-4;                    // 在要跟踪的点上添加一些偏差
        if (raydir.dot(nhit) > 0)             // 如果法线和视图方向不相反，反转法线方向
        {
            nhit = -nhit;
        }
        if ((orb->transparency > 0 || orb->reflection > 0) && depth < MAX_RAY_DEPTH)
        {
            // 进行反射计算
            float IdotN = raydir.dot(nhit);                 // 光线方向规范化
            float facingratio = std::max(float(0), -IdotN); // 如果 -IdotN为负，说明在视点背面，不用显示，取0
            // 不同光波分量被折射和反射，当视线垂直于表面时，反射较弱，而当视线非垂直表面时，夹角越小，反射越明显(菲涅尔效应)
            float fresneleffect = mix(pow(1 - facingratio, 3), 1, 0.1); // 菲涅尔效应
            Vecf refldir;                                               // 反射光线
            refldir = raydir - nhit * 2 * raydir.dot(nhit);             // r = d + 2 ( d·n ) n 反射光线计算公式（PPT里出现的
            refldir.normalize();                                        // 反射光线向量规范化
            // 递归调用
            Vecf reflection = trace(phit + nhit * bias, refldir, orbs, depth + 1); // 交点作为原点，进行光线追踪，递归深度++ 返回颜色

            Vecf refraction = 0; // 初始化折射率
            // 如果透明度不为零，进行折射计算
            if (orb->transparency > 0)
            {
                // 折射
                float ior = 1.2;                                                  // 折射系数
                float eta = 1 / ior;                                              // 折射率
                float k = 1 - eta * eta * (1 - IdotN * IdotN);                    // 菲涅尔折射系数
                Vecf refrdir = raydir * eta - nhit * (eta * IdotN + sqrt(k));     // 方向向量乘上折射率，然后加上菲涅尔效应的影响
                refrdir.normalize();                                              // 折射光线规范化
                refraction = trace(phit - nhit * bias, refrdir, orbs, depth + 1); // 交点作为原点，进行光线追踪，递归深度++ 返回颜色
            }
            // 结果是反射和折射的混合（如果球体是透明的）
            surfaceColor =
                (reflection * fresneleffect +                          // 反射部分的颜色
                 refraction * (1 - fresneleffect) * orb->transparency) // 折射部分的颜色
                * orb->surfaceColor;                                   // 两者的和乘上物体表面颜色，得到最后颜色
            // R(color(p+tr)+(1-R)color(p+t*t))
        }
        else
        {
            // 这是一个折射率和反射率为0的物体，不需要再进行光线追踪
            double shadow = 1.0;
            for (unsigned i = 0; i < orbs.size(); ++i) // 遍历每个物体，依次计算是否相交，相交的话更新阴影
            {
                if (orbs[i]->emissionColor.x > 0)
                {
                    Vecf transmission = 1.0;                      // 初始化
                    Vecf lightDirection = orbs[i]->center - phit; // 球体法向量
                    lightDirection.normalize();                   // 法向量规范化

                    for (unsigned j = 0; j < orbs.size(); ++j)
                    {
                        if (i != j)
                        {
                            float t0, t1;
                            // 判断该点的光是否和源光线相交，如果相交，计算阴影
                            if (orbs[j]->intersect(phit + (nhit * bias), lightDirection, &t0, &t1))
                            {
                                shadow = std::max(0.0, shadow - (1.0 - orbs[j]->transparency)); // 相交的话更新折射率
                                transmission = transmission * shadow;                           // 计算转化率
                            }
                        }
                    }

                    // 用phong模型计算每一条对这点像素造成影响的光线
                    surfaceColor += orb->surfaceColor * transmission * orbs[i]->emissionColor; // 加上最后传递的颜色
                }
            }
        }
        return surfaceColor; // 返回最终的颜色
    }
    else
    {
        return Vecf(1.0, 1.0, 1.0); // 背景为白色
    }
}

// 为图像的每个像素计算一条光线，跟踪它并返回一个颜色
// 如果光线击中球体，则返回相交点处球体的颜色，否则返回背景色
void render(const std::vector<orb *> &orbs, GLFWwindow *window)
{
    // 一些用于计算的参数设置
    Vecf *image = new Vecf[WIDTH * HEIGHT], *pixel = image;
    float invWidth = 1 / float(WIDTH), invHeight = 1 / float(HEIGHT); // 计算屏占比
    float fov = 40, aspectratio = WIDTH / float(HEIGHT);              // 设定视场角（视野范围） 和 纵横比
    float angle = tan(M_PI * 0.5 * fov / 180.0);                      // 把市场角转化为普通的角度

    // 光线追踪开始，逐像素点进行光线追踪
    for (unsigned y = 0; y < HEIGHT; ++y)
    {
        for (unsigned x = 0; x < WIDTH; ++x, ++pixel)
        {
            // 进行坐标系的转换
            float xx = (2 * ((x + 0.5) * invWidth) - 1) * angle * aspectratio;
            float yy = (1 - 2 * ((y + 0.5) * invHeight)) * angle;
            Vecf raydir(xx, yy, -1); // z的值决定
            raydir.normalize();
            *pixel = trace(Vecf(0), raydir, orbs, 0);
        }
    }

    std::vector<float> vertices;
    for (unsigned int i = 0; i < HEIGHT; i++)
    {
        for (unsigned int j = 0; j < WIDTH; j++)
        {
            // 坐标转换
            auto a = -2 * (float(j) / WIDTH - 0.5);
            auto b = -2 * (float(i) / HEIGHT - 0.5);
            vertices.push_back(a);
            vertices.push_back(b);
            vertices.push_back(0);
            // 设置颜色值
            vertices.push_back(min(image[i * WIDTH + j].x, float(1)));
            vertices.push_back(min(image[i * WIDTH + j].y, float(1)));
            vertices.push_back(min(image[i * WIDTH + j].z, float(1)));
        }
    }
    Shader OurShader(
        "/home/xhd0728/BallTracing/balls/3.3.shader.vert",
        "/home/xhd0728/BallTracing/balls/3.3.shader.frag");
    OurShader.use();
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * 4, &vertices[0], GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    while (!glfwWindowShouldClose(window))
    {
        // 响应事件
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClearDepth(1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDrawArrays(GL_POINTS, 0, vertices.size() / 6);
        glEnable(GL_DEPTH_TEST); // 深度测试
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();
}

void key_call_back(GLFWwindow *window, int key, int scancode, int action, int mode);

int main(int argc, char **argv)
{
    glfwInit();                                                    // 初始化GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);                 // OpenGL主版本号 3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);                 // OpenGL副版本号 .3
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // OpenGL模式 OpenGL核心模式

    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr); // 窗口宽、高、标题
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_call_back);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    std::vector<orb *> orbs;
    // 底面的大球
    orbs.push_back(new orb(Vecf(0, -10004, -20), 10000, Vecf(1.0, 1.0, 1.0), 1.0, 0.0));
    // 6个小球
    // 红球
    orbs.push_back(new orb(Vecf(6, 0, -15), 1.5, Vecf(1.00, 0.1, 0.1), 0.2, 0.95));
    // 蓝球
    orbs.push_back(new orb(Vecf(7.5, 2.5, -25), 2, Vecf(0.1, 0.1, 1.0), 0.2, 0.7));
    // 透明球
    orbs.push_back(new orb(Vecf(1, -1, -18), 1, Vecf(1.0, 1.0, 1.0), 0.1, 1.0));
    // 黑球
    orbs.push_back(new orb(Vecf(2, 1, -25), 2, Vecf(1.0, 1.0, 1.0), 0.3, 0.0));
    // 黄球
    orbs.push_back(new orb(Vecf(-2, 2, -15), 1, Vecf(1.0, 1.0, 0.1), 0.5, 0.5));
    // 绿球
    orbs.push_back(new orb(Vecf(-4, 3, -18), 1, Vecf(0.1, 1.0, 0.1), 0.3, 0.7));
    // 蓝球
    orbs.push_back(new orb(Vecf(-8, 0, -25), 0.5, Vecf(0.36, 0.84, 1.0), 0.15, 0.95));
    // 红球
    orbs.push_back(new orb(Vecf(-8.5, -1.5, -25), 1, Vecf(1.00, 0.1, 0.1), 0.15, 0.5));

    render(orbs, window);
    return 0;
}

void key_call_back(GLFWwindow *window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}