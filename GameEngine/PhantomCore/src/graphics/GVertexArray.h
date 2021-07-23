#ifndef _GL_VERTEXARRAY_H_
#define _GL_VERTEXARRAY_H_
#include <glad/glad.h>
#include <vector>
#include "GVertexBuffer.h"
namespace Phantom
{
    namespace graphics
    {
        class GVertexArray
        {
        public:
            GVertexArray(/* args */);
            virtual ~GVertexArray();
            void bind() const;
            void unbind() const;
            void addBuffer(GVertexBuffer *buffer, GLuint index);

        private:
            GLuint m_vertexArrayId;
            std::vector<GVertexBuffer *> vertexarray;
        };

    }
}
#endif