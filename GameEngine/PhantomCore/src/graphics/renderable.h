#pragma once
#include "../maths/maths.h"
#include "GVertexArray.h"
#include "shader.h"
using namespace phantom::maths;
namespace phantom
{
    namespace graphics
    {
        class renderable
        {
        private:
            vec3 m_position;
            vec3 m_color;
            Shader &m_shader;
            GVertexArray *m_Vao;

        public:
            renderable(vec3 color, vec3 position, Shader &shader);

            inline const GVertexArray *getVAO() const { return m_Vao; }
            inline Shader &getShader() const { return m_shader; }
            inline const vec3 &getPosition() const { return m_position; }
            inline const vec3 &getColor() const { return m_color; }

            virtual ~renderable();
        };
    }
}