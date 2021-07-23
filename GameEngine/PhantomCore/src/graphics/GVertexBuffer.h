#ifndef _GL_VERTEXBUFFER_H_
#define _GL_VERTEXBUFFER_H_
#include <glad/glad.h>
namespace Phantom
{
    namespace graphics
    {
        class GVertexBuffer
        {
        public:
            inline void bind() { glBindBuffer(GL_ARRAY_BUFFER, m_bufferId); };
            inline void unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); };
            GLuint getComponentCount() const { return m_ComponentCount; };
            GVertexBuffer(GLfloat *data, GLsizei size, GLuint componentCount);
            virtual ~GVertexBuffer();

        private:
            GLuint m_bufferId;
            GLuint m_ComponentCount;
        };
    }
}

#endif