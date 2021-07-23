#include "GIndexBuffer.h"
namespace Phantom
{
    namespace graphics
    {
        GIndexBuffer::GIndexBuffer(GLfloat *data, GLsizei count)
        {
            glGenBuffers(1, &m_BufferId);
            glBindBuffer(GL_ARRAY_BUFFER, m_BufferId);
            glBufferData(GL_ARRAY_BUFFER, count, data, GL_STATIC_DRAW);
        }

        GIndexBuffer::~GIndexBuffer()
        {
            glDeleteBuffers(GL_ELEMENT_ARRAY_BUFFER, &m_BufferId);
        }
    }
}
