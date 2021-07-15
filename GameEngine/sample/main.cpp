#include "src/graphics/window.h"
#include "src/maths/maths.h"
#include "src/utils/fileUtils.h"
#include <iostream>
#include <string>
#include <windows.h>
using namespace phantom::maths;

GLint m_ShaderId;
double mouse_x = 0.0;
double mouse_y = 0.0;

//获取索引值
GLint getUniformLocation(const GLchar *name)
{
    return glGetUniformLocation(m_ShaderId, name);
}

//输出shade日志信息
void printShaderInfoLog(GLuint obj)
{
    int infoLenght = 0;
    int charsWriteLen = 0;
    char *infoLog;
    //获取指定的shader对象信息
    glGetShaderiv(obj, GL_INFO_LOG_LENGTH, &infoLenght);

    if (infoLenght > 0)
    {
        infoLog = (char *)malloc(infoLenght);
        //获取着色器对象日志
        glGetShaderInfoLog(obj, infoLenght, &charsWriteLen, infoLog);
        printf("%s\n", infoLog);
        free(infoLog);
    }
}

//输出Program日志信息
void printProgramInfoLog(GLuint obj)
{
    int infoLenght = 0;
    int charsWriteLen = 0;
    char *infoLog;
    //获取指定的Program对象信息
    glGetProgramiv(obj, GL_INFO_LOG_LENGTH, &infoLenght);

    if (infoLenght > 0)
    {
        infoLog = (char *)malloc(infoLenght);
        //返回program对象的信息日志
        glGetProgramInfoLog(obj, infoLenght, &charsWriteLen, infoLog);
        printf("%s\n", infoLog);
        free(infoLog);
    }
}

GLint setupShader()
{
    char *vs = NULL, *fs = NULL;
    GLuint p, v, f;
    //创建一个着色器对象
    v = glCreateShader(GL_VERTEX_SHADER);
    f = glCreateShader(GL_FRAGMENT_SHADER);

    vs = readFile("shaders/vert.shader");

    fs = readFile("shaders/frag.shader");

    //替换shader中的源代码
    glShaderSource(v, 1, &vs, NULL);
    glShaderSource(f, 1, &fs, NULL);
    //编译一个着色器对象
    glCompileShader(v);
    glCompileShader(f);
	free(vs);
	free(fs);
    printShaderInfoLog(v);
    printShaderInfoLog(f);

    //创建一个program
    p = glCreateProgram();
    //将着色器添加到program中
    glAttachShader(p, v);
    glAttachShader(p, f);

    //连接一个program对象
    glLinkProgram(p);
    printProgramInfoLog(p);

    //删除着色器
    glDeleteShader(v);
    glDeleteShader(f);
    return p;
}

int main()
{
	char curPath[MAX_PATH];
	GetCurrentDirectoryA(MAX_PATH, curPath);
	printf("当前工作目录%s", curPath);
	

    using namespace phantom;
    using namespace graphics;

    Window window("phantom!", 960, 540);
    glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

    m_ShaderId = setupShader();

    //创建顶点数据
    GLfloat vertices[] = {
        -0.5f, 0.0f, 0.0f,
        0.5f, 0.0f, 0.0f,
        0.0f, 0.5f, 0.0f};
    GLuint vaoId, vboId;
    //创建vao
    glGenVertexArrays(1, &vaoId);
    glBindVertexArray(vaoId);
    //创建vbo
    glGenBuffers(1, &vboId);
    glBindBuffer(GL_ARRAY_BUFFER, vboId);

    //构建顶点缓存并复制
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    //提交顶点数据到Gpu
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (GLvoid *)0);
    //设置索引位置
    glEnableVertexAttribArray(0);

#if (1)
    mat4x4 m2(0, 4, 8, 12,
              1, 5, 9, 13,
              2, 6, 10, 14,
              3, 7, 11, 15);
    vec3 v(10, 1, 1);
    mat4x4 m4 = mat4x4::scale(v);
    std::cout << m4;
    mat4x4 m3 = m4 * m2;
    std::cout << m3;
    m2.scale(10, 1, 1);
    std::cout << m2;
#endif
    while (!window.closed())
    {
        window.clear();
        glUseProgram(m_ShaderId);
        glColor3f(0.2f, 0.3f, 0.8f);
        glBindVertexArray(vaoId);
        //命令GPU绘制函数,一般用glDrawArrays/glDrawEmlement
        glDrawArrays(GL_TRIANGLES, 0, 3); //参数1：绘制三角形方式,参数2:其实位置,一般为0,参数3:绘制顶点数
        window.update();
    }
    //终止window
    glDeleteVertexArrays(1, &vaoId);
    glDeleteBuffers(1, &vboId);
    window.terminate();

    return 0;
}