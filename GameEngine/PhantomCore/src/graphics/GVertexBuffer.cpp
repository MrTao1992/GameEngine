#include "GVertexBuffer.h"
namespace phantom
{
    namespace graphics
    {
        GVertexBuffer::GVertexBuffer(GLfloat *data, GLsizei size, GLuint componentCount) : m_ComponentCount(componentCount)
        {
            glGenBuffers(1, &m_bufferId);
            glBindBuffer(GL_ARRAY_BUFFER, m_bufferId);
            glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        GVertexBuffer::~GVertexBuffer()
        {
            glDeleteBuffers(GL_ELEMENT_ARRAY_BUFFER, &m_bufferId);
        }

    }
}