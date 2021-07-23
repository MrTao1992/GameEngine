#include "shader.h"
#include "../utils/fileUtils.h"

namespace Phantom
{
    namespace graphics
    {
        Shader::Shader(const char *_vfilename, const char *_ffilename)
        {
            fPath = _ffilename;
            vPath = _vfilename;
            m_ShaderId = compile();
        }
        Shader::~Shader()
        {
            glDeleteProgram(m_ShaderId);
        };
        void Shader::bind()
        {
            glUseProgram(m_ShaderId);
        };
        void Shader::unbind()
        {
            glUseProgram(0);
        };

        // 设置uniform输入数据
        void Shader::setUniform1f(const GLchar *name, float f)
        {
            glUniform1f(getUniformLocation(name), f);
        };
        void Shader::setUniform1i(const GLchar *name, float i)
        {
            glUniform1i(getUniformLocation(name), i);
        };
        void Shader::setUniform2f(const GLchar *name, const maths::vec2 &v2)
        {
            glUniform2f(getUniformLocation(name), v2.x, v2.y);
        };
        void Shader::setUniform3f(const GLchar *name, const maths::vec3 &v3)
        {
            glUniform3f(getUniformLocation(name), v3.x, v3.y, v3.z);
        };
        void Shader::setUniform4f(const GLchar *name, const maths::vec4 &v4)
        {
            glUniform4f(getUniformLocation(name), v4.x, v4.y, v4.z, v4.w);
        };
        void Shader::setUniformMat4(const GLchar *name, const maths::mat4x4 &m4)
        {
            glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, m4.elements);
        };

        //编译一个着色器对象
        GLint Shader::compile()
        {
            //加载文件
            char *vs = NULL, *fs = NULL;
            vs = readFile(vPath);
            fs = readFile(fPath);
            //创建shader着色器
            GLint compileRes;
            GLint vShader = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vShader, 1, &vs, NULL);
            glCompileShader(vShader);
            glGetShaderiv(vShader, GL_COMPILE_STATUS, &compileRes);
            if (compileRes == GL_FALSE)
            {
                printShaderInfoLog(vShader);
            }
            GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fShader, 1, &fs, NULL);
            glCompileShader(fShader);
            glGetShaderiv(fShader, GL_COMPILE_STATUS, &compileRes);
            if (compileRes == GL_FALSE)
            {
                printShaderInfoLog(fShader);
            }
            // free(vs);
            // free(fs);
            //创建program,bind着色器
            GLuint compilingPId = glCreateProgram();
            glAttachShader(compilingPId, vShader);
            glAttachShader(compilingPId, fShader);
            glLinkProgram(compilingPId);
            printProgramInfoLog(compilingPId);

            glDeleteShader(vShader);
            glDeleteShader(fShader);

            return compilingPId;
        }
        // 输出Program日志信息
        void Shader::printProgramInfoLog(GLint id)
        {
            int infoLenght = 0;
            int charsWriteLen = 0;
            char *infoLog;
            //获取指定的Program对象信息
            glGetProgramiv(id, GL_INFO_LOG_LENGTH, &infoLenght);

            if (infoLenght > 0)
            {
                infoLog = (char *)malloc(infoLenght);
                //返回program对象的信息日志
                glGetProgramInfoLog(id, infoLenght, &charsWriteLen, infoLog);
                printf("%s\n", infoLog);
                free(infoLog);
            }
        }
        // 输出shade日志信息
        void Shader::printShaderInfoLog(GLint id)
        {
            int infoLenght = 0;
            int charsWriteLen = 0;
            char *infoLog;
            //获取指定的shader对象信息
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &infoLenght);

            if (infoLenght > 0)
            {
                infoLog = (char *)malloc(infoLenght);
                //获取着色器对象日志
                glGetShaderInfoLog(id, infoLenght, &charsWriteLen, infoLog);
                printf("%s\n", infoLog);
                free(infoLog);
            }
        }
        // 获取索引值
        GLint Shader::getUniformLocation(const GLchar *name) { return glGetUniformLocation(m_ShaderId, name); };
    }
}
