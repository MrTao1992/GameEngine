#include "BaseApplication.h"
#include "GraphicsManager.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
namespace Phantom
{
    class DefaultApplication : public BaseApplication
    {
    public:
        DefaultApplication(GfxConfiguration &config);
        virtual int Initialize();
        virtual void Finalize();
        virtual void Tick();

    private:
        GLFWwindow *m_Window;
        static void windowResize(GLFWwindow *window, int width, int height);
        //添加键盘事件回调
        static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
        //添加鼠标事件
        static void cursor_position_callback(GLFWwindow *window, double xpos, double ypos);
    };
}