#ifndef _FILE_SHADER_H_
#define _FILE_SHADER_H_

#include <GL/glew.h>
#include "../maths/maths.h"
namespace phantom
{
    namespace graphics
    {
        class Shader
        {
        public:
            Shader(const char *_vfilename, const char *_ffilename);
            ~Shader();
            GLint m_ShaderId;
            void bind();
            void unbind();

            //设置uniform输入数据
            void setUniform1f(const GLchar *name, float f);
            void setUniform1i(const GLchar *name, float i);
            void setUniform2f(const GLchar *name, const maths::vec2 &v2);
            void setUniform3f(const GLchar *name, const maths::vec3 &v3);
            void setUniform4f(const GLchar *name, const maths::vec4 &v4);
            void setUniformMat4(const GLchar *name, const maths::mat4x4 &m4);

        private:
            const char *vPath;
            const char *fPath;
            //编译一个着色器对象
            GLint compile();
            //输出Program日志信息
            void printProgramInfoLog(GLint id);
            //输出shade日志信息
            void printShaderInfoLog(GLint id);
            //获取索引值
            GLint getUniformLocation(const GLchar *name);
        };
    }
}

#endif