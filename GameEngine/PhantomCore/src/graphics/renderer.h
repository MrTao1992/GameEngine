#pragma once
#include <glad/glad.h>
#include "renderable.h"
#include <deque>
extern const char *MVP_NAME_M;
extern const char *MVP_NAME_V;
extern const char *MVP_NAME_P;
namespace phantom
{
    namespace graphics
    {
        class renderer
        {
        private:
            std::deque<const renderable *> m_RenderQueue;

        public:
            virtual void submit(const renderable *able);
            virtual void flush();
        };
    }
}