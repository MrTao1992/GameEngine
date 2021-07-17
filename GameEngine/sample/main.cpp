#include "src/graphics/window.h"
#include "src/maths/maths.h"
#include "src/graphics/shader.h"
#include <iostream>
#include <string>
#include <windows.h>
using namespace phantom::maths;

using namespace phantom;
using namespace graphics;
double mouse_x = 0.0;
double mouse_y = 0.0;

int main()
{
    char curPath[MAX_PATH];
    GetCurrentDirectoryA(MAX_PATH, curPath);
    printf("当前工作目录%s", curPath);

    Window window("phantom!", 960, 540);
    glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
    Shader shader("shaders/vert_light.shader", "shaders/frag_light.shader");
    GLint m_ShaderId = shader.m_ShaderId;
    shader.bind();
    //创建顶点数据
    // GLfloat vertices[] = {
    //     0.5f, -0.5f, 0.0f,  // 右下角
    //     -0.5f, -0.5f, 0.0f, // 左下角
    //     -0.5f, 0.5f, 0.0f   // 左上角
    // };

    //创建正方形顶点数据
    GLfloat vertices[] = {
        -1.0f, -1.0f, -1.0f, // triangle 1 : begin
        -1.0f, -1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f, // triangle 1 : end
        1.0f, 1.0f, -1.0f, // triangle 2 : begin
        -1.0f, -1.0f, -1.0f,
        -1.0f, 1.0f, -1.0f, // triangle 2 : end
        1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, 1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, -1.0f,
        1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, 1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, -1.0f,
        -1.0f, 1.0f, -1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, -1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 1.0f};
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

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // mat4x4 pm = mat4x4::orthographic(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
    mat4x4 pm = mat4x4::perspective(200.0f, 16.0 / 9.0f, -1.0f, 1.0f);
    shader.setUniformMat4("projection_matrix", pm);
    shader.setUniform2f("light_pos", vec2(4.0f, 1.5f));
    shader.setUniform4f("color_light", vec4(1.0f, 0.7f, 0.8f, 1.0f));
    shader.setUniform1f("factor_light", 0.3f);

    // #if (1)
    //     mat4x4 m2(0, 4, 8, 12,
    //               1, 5, 9, 13,
    //               2, 6, 10, 14,
    //               3, 7, 11, 15);
    //     vec3 v(10, 1, 1);
    //     mat4x4 m4 = mat4x4::scale(v);
    //     std::cout << m4;
    //     mat4x4 m3 = m4 * m2;
    //     std::cout << m3;
    //     m2.scale(10, 1, 1);
    //     std::cout << m2;
    // #endif
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    while (!window.closed())
    {
        window.clear();
        glBindVertexArray(vaoId);
        shader.setUniform2f("light_pos", vec2((float)(mouse_x * 1.0f / 960.0f - 0.5f), (float)(0.5f - mouse_y * 1.0f / 540.0f)));
        //命令GPU绘制函数,一般用glDrawArrays/glDrawEmlement
        glDrawArrays(GL_TRIANGLES, 0, 3 * 12);
        glBindVertexArray(0);
        window.update();
    }
    //终止window
    shader.unbind();
    window.terminate();

    return 0;
}