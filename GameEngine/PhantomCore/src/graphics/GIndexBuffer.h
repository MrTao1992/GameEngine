#ifndef _GL_INDEXBUFFER_H_
#define _GL_INDEXBUFFER_H_
#include <glad/glad.h>

namespace phantom
{
    namespace graphics
    {
        class GIndexBuffer
        {
        private:
            GLuint m_BufferId;
            GLuint m_Count;

        public:
            GIndexBuffer(GLfloat *data, GLsizei count);
            virtual ~GIndexBuffer();

            inline void bind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferId); }
            inline void unbind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

            inline GLuint getCount() const { return m_Count; }
        };
    }
}

#endif