#include "window.h"
#include "maths.h"
#include "shader.h"
#include <iostream>
#include <string>
#include <windows.h>
#include "renderer.h"
using namespace Phantom::maths;

using namespace Phantom;
using namespace Phantom::graphics;
double mouse_x = 0.0;
double mouse_y = 0.0;
const char *MVP_NAME_M = "ojbect2world_matrix";
const char *MVP_NAME_V = "world2view_matrix";
const char *MVP_NAME_P = "projection_matrix";
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

    renderable sp1(vec3(0, 1, 0), vec3(0.3f, 0.3f, 0.3f), shader);
    renderable sp2(vec3(1.0, 1.0, 0.8), vec3(1.0f, 0.3f, 0.3f), shader);
    renderable sp3(vec3(0.8, 1.0, 1.0), vec3(0.3f, 1.0f, 0.3f), shader);
    renderable sp4(vec3(0.7, 0.2, 0.8), vec3(0.3f, 0.3f, 1.0f), shader);
    renderable sp5(vec3(1.7, 0.2, 1.0), vec3(1.0f, 0.3f, 1.0f), shader);
    // mat4x4 pm = mat4x4::orthographic(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
    mat4x4 proMat(1.0f);
    // proMat.orthographic(-2.0f, 2.0f, -2.0f, 2.0f, 0.01f, 1000.0f);
    // proMat.perspective(120.0f, 16.0f / 9.0f, 0.01f, 1000.0f);
    // proMat.orthographic(-5.0f, 5.0f, -5.0f, 5.0f, 0.01f, 1000.0f);
    proMat.perspective(90.0f, 16.0f / 9.0f, 0.01f, 1000.0f);
    mat4x4 viewMat(1.0f);
    viewMat.LookAtMatrixBuild(vec3(0, 0, 2), vec3(0, 0, 0), vec3(0, 1, 0));
    std::cout << viewMat << std::endl;

    shader.setUniformMat4(MVP_NAME_V, viewMat);
    shader.setUniformMat4(MVP_NAME_P, proMat);
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
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    GLfloat radius = 5.0f;
    renderer *renders = new renderer();
    while (!window.closed())
    {
        //每帧清理颜色，深度，顶点数据
        window.clear();
        GLfloat camX = sin(glfwGetTime()) * radius;
        GLfloat camZ = cos(glfwGetTime()) * radius;
        viewMat.LookAtMatrixBuild(vec3(camX, 0.0f, camZ), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
        shader.setUniformMat4(MVP_NAME_V, viewMat);
        shader.setUniform2f("light_pos", vec2((float)(mouse_x * 1.0f / 960.0f - 0.5f), (float)(0.5f - mouse_y * 1.0f / 540.0f)));
        //命令GPU绘制函数,一般用glDrawArrays/glDrawEmlement
        renders->submit(&sp1);
        renders->submit(&sp2);
        renders->submit(&sp3);
        renders->submit(&sp4);
        renders->submit(&sp5);
        renders->flush();
        window.update();
    }
    //终止window
    shader.unbind();
    window.terminate();

    return 0;
}