#include "src/graphics/window.h"
#include "src/maths/maths.h"
using namespace phantom::maths;
int main()
{
    using namespace phantom;
    using namespace graphics;

    Window window("phantom!", 960, 540);
    glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
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
    //上传通道开关
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
        glBindVertexArray(vaoId);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        window.update();
    }
    window.terminate();

    return 0;
}