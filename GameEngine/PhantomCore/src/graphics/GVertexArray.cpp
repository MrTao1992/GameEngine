#include "GVertexArray.h"
namespace phantom
{
    namespace graphics
    {
        GVertexArray::GVertexArray()
        {
            glGenVertexArrays(1, &m_vertexArrayId);
        }
        GVertexArray::~GVertexArray()
        {
            size_t count = vertexarray.size();
            for (size_t i = 0; i < count; i++)
            {
                delete vertexarray[i];
            }
        }
        void GVertexArray::bind() const
        {
            glBindVertexArray(m_vertexArrayId);
        };
        void GVertexArray::unbind() const
        {
            glBindVertexArray(0);
        };
        void GVertexArray::addBuffer(GVertexBuffer *buffer, GLuint index)
        {
            bind();
            buffer->bind();
            glVertexAttribPointer(index, buffer->getComponentCount(), GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)0);
            glEnableVertexAttribArray(index);
            buffer->unbind();
            unbind();
        };

    }
}