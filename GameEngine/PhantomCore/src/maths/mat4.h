#pragma once

#include <iostream>
#include "vector.h"
// 二维，三维，四维矩阵排列顺序
// | 0 2 |    | 0 3 6 |    |  0  4  8 12 |
// | 1 3 |    | 1 4 7 |    |  1  5  9 13 |
//            | 2 5 8 |    |  2  6 10 14 |
//                         |  3  7 11 15 |

// 4x4 matrix
namespace phantom
{
    namespace maths
    {
        struct mat4x4
        {
            union
            {
                float elements[4 * 4];
                vec4 columns[4];
            };
            mat4x4();
            mat4x4(float diagonal);
            mat4x4(float m00, float m01, float m02, float m03,  // 1st column
                   float m04, float m05, float m06, float m07,  // 2nd column
                   float m08, float m09, float m10, float m11,  // 3rd column
                   float m12, float m13, float m14, float m15); // 4th column
            mat4x4 operator*(const mat4x4 &other);
            inline vec4 getColumn(int index)
            {
                index *= 4;
                return vec4(elements[index], elements[index + 1], elements[index + 2], elements[index + 3]);
            }

            mat4x4 operator+(const mat4x4 &other);
            mat4x4 rotation(float angle, const vec3 &axis);
            //transform matrix
            mat4x4 &translate(float x, float y, float z);
            static mat4x4 translation(const vec3 &translation);
        };

    }
}