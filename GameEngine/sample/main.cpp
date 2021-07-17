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
    //创建顶点颜色数据
    GLfloat colors[] = {
        0.583f, 0.771f, 0.014f,
        0.609f, 0.115f, 0.436f,
        0.327f, 0.483f, 0.844f,
        0.822f, 0.569f, 0.201f,
        0.435f, 0.602f, 0.223f,
        0.310f, 0.747f, 0.185f,
        0.597f, 0.770f, 0.761f,
        0.559f, 0.436f, 0.730f,
        0.359f, 0.583f, 0.152f,
        0.483f, 0.596f, 0.789f,
        0.559f, 0.861f, 0.639f,
        0.195f, 0.548f, 0.859f,
        0.014f, 0.184f, 0.576f,
        0.771f, 0.328f, 0.970f,
        0.406f, 0.615f, 0.116f,
        0.676f, 0.977f, 0.133f,
        0.971f, 0.572f, 0.833f,
        0.140f, 0.616f, 0.489f,
        0.997f, 0.513f, 0.064f,
        0.945f, 0.719f, 0.592f,
        0.543f, 0.021f, 0.978f,
        0.279f, 0.317f, 0.505f,
        0.167f, 0.620f, 0.077f,
        0.347f, 0.857f, 0.137f,
        0.055f, 0.953f, 0.042f,
        0.714f, 0.505f, 0.345f,
        0.783f, 0.290f, 0.734f,
        0.722f, 0.645f, 0.174f,
        0.302f, 0.455f, 0.848f,
        0.225f, 0.587f, 0.040f,
        0.517f, 0.713f, 0.338f,
        0.053f, 0.959f, 0.120f,
        0.393f, 0.621f, 0.362f,
        0.673f, 0.211f, 0.457f,
        0.820f, 0.883f, 0.371f,
        0.982f, 0.099f, 0.879f};
    GLuint vaoId, vboId, colorId;
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

    //创建颜色索引
    glGenBuffers(1, &colorId);
    glBindBuffer(GL_ARRAY_BUFFER, colorId);
    //构建颜色缓存并复制
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
    //提交顶点数据到Gpu
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (GLvoid *)0);
    //设置索引位置
    glEnableVertexAttribArray(1);

    // mat4x4 pm = mat4x4::orthographic(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
    mat4x4 proMat(1.0f);
    // proMat.orthographic(-2.0f, 2.0f, -2.0f, 2.0f, 0.01f, 1000.0f);
    proMat.perspective(120.0f, 16.0f / 9.0f, 0.01f, 1000.0f);
    mat4x4 viewMat(1.0f);
    viewMat.LookAtMatrixBuild(vec3(0, 0, 2), vec3(0, 0, 0), vec3(0, 1, 0));
    std::cout << viewMat << std::endl;

    shader.setUniformMat4("world2view_matrix", viewMat);
    shader.setUniformMat4("projection_matrix", proMat);
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
        //每帧清理颜色，深度，顶点数据
        window.clear();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        viewMat.LookAtMatrixBuild(vec3(0.0f, 0.0f, 2.0f), vec3(2.0f * (mouse_x / 960.0f - 0.5f), -(mouse_y / 540.0f - 0.5f) * 2.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
        viewMat.LookAtMatrixBuild(vec3(2.0f * (mouse_x / 960.0f - 0.5f), -(mouse_y / 540.0f - 0.5f) * 2.0f, 2.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
        shader.setUniformMat4("world2view_matrix", viewMat);
        shader.setUniform2f("light_pos", vec2((float)(mouse_x * 1.0f / 960.0f - 0.5f), (float)(0.5f - mouse_y * 1.0f / 540.0f)));
        //命令GPU绘制函数,一般用glDrawArrays/glDrawEmlement
        glBindVertexArray(vaoId);
        glDrawArrays(GL_TRIANGLES, 0, 3 * 12);
        window.update();
    }
    //终止window
    shader.unbind();
    window.terminate();

    return 0;
}