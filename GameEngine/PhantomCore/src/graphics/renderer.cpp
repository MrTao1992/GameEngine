#include "renderer.h"
namespace Phantom
{
    namespace graphics
    {
        void renderer::submit(const renderable *able)
        {
            m_RenderQueue.push_back(able);
        }
        void renderer::flush()
        {
            while (!m_RenderQueue.empty())
            {
                const renderable *renderable = m_RenderQueue.front();
                renderable->getVAO()->bind();

                mat4x4 m = mat4x4::translation(renderable->getPosition());
                renderable->getShader().setUniformMat4(MVP_NAME_M, m);

                glDrawArrays(GL_TRIANGLES, 0, 12 * 3);

                renderable->getVAO()->unbind();
                m_RenderQueue.pop_front();
            }
        }
    }
}