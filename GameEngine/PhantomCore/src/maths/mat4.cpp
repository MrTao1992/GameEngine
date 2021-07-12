#include "mat4.h"
#include "utils.h"
namespace phantom
{
    namespace maths
    {
        mat4x4::mat4x4()
        {
            for (int i = 0; i < 4 * 4; i++)
            {
                elements[i] = 0.0f;
            }
        }

        mat4x4::mat4x4(float diagonal)
        {
            for (int i = 0; i < 16; i++)
            {
                i % 4 == 0 ? elements[i] = diagonal : elements[i] = 0.0f;
            }
        }

        mat4x4::mat4x4(float m00, float m01, float m02, float m03, // 1st column
                       float m04, float m05, float m06, float m07, // 2nd column
                       float m08, float m09, float m10, float m11, // 3rd column
                       float m12, float m13, float m14, float m15) // 4th column
        {
            elements[0] = m00;
            elements[1] = m01;
            elements[2] = m02;
            elements[3] = m03;
            elements[4] = m04;
            elements[5] = m05;
            elements[6] = m06;
            elements[7] = m07;
            elements[8] = m08;
            elements[9] = m09;
            elements[10] = m10;
            elements[11] = m11;
            elements[12] = m12;
            elements[13] = m13;
            elements[14] = m14;
            elements[15] = m15;
        }

        mat4x4 mat4x4::operator+(const mat4x4 &other)
        {
            mat4x4 result(0);
            for (int column = 0; column < 4; column++)
            {
                for (int row = 0; row < 4; row++)
                {
                    float sum = 0.0f;
                    for (int i = 0; i < 4; i++)
                    {
                        sum = elements[row + 4 * i] + other.elements[column * 4 + i];
                    }
                    result.elements[column * 4 + row] = sum;
                }
            }
            return result;
        }

        mat4x4 mat4x4::operator*(const mat4x4 &other)
        {
            mat4x4 result(0);
            for (int column = 0; column < 4; column++)
            {
                for (int row = 0; row < 4; row++) //column * cow 共计计算16个元素
                {
                    float sum = 0.0f;
                    for (int i = 0; i < 4; i++)
                    {
                        sum += elements[row + 4 * i]             //左矩阵行向量
                               * other.elements[i + column * 4]; //右矩阵列向量
                    }
                    result.elements[column * 4 + row] = sum;
                }
            }
            return result;
        }

        mat4x4 mat4x4::translation(const vec3 &translation)
        {
            mat4x4 result(1.0f);

            result.elements[0 + 3 * 4] = translation.x;
            result.elements[1 + 3 * 4] = translation.y;
            result.elements[2 + 3 * 4] = translation.z;

            return result;
        }

        mat4x4 mat4x4::rotation(float angle, const vec3 &axis)
        {
            mat4x4 result(1.0f);

            float r = toRadians(angle);
            float c = cos(r);
            float s = sin(r);
            float omc = 1.0f - c;

            float x = axis.x;
            float y = axis.y;
            float z = axis.z;

            result.elements[0 + 0 * 4] = x * omc + c;
            result.elements[1 + 0 * 4] = y * x * omc + z * s;
            result.elements[2 + 0 * 4] = x * z * omc - y * s;

            result.elements[0 + 1 * 4] = x * y * omc - z * s;
            result.elements[1 + 1 * 4] = y * omc + c;
            result.elements[2 + 1 * 4] = y * z * omc + x * s;

            result.elements[0 + 2 * 4] = x * z * omc + y * s;
            result.elements[1 + 2 * 4] = y * z * omc - x * s;
            result.elements[2 + 2 * 4] = z * omc + c;

            return result;
        }
    }
}
