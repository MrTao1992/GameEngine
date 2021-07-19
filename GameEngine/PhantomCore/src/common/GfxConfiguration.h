#pragma once
#include <iostream>
//增加引擎配置文件
namespace Phantom
{
    struct GfxConfiguration
    {
        /// Inline all-elements constructor.
        // / \param[in] r the red color depth in bits
        // / \param[in] g the green color depth in bits
        // / \param[in] b the blue color depth in bits
        // / \param[in] a the alpha color depth in bits
        // / \param[in] d the depth buffer depth in bits
        // / \param[in] s the stencil buffer depth in bits
        // / \param[in] msaa the msaa sample count
        // / \param[in] width the screen width in pixel
        // / \param[in] height the screen height in pixel

        uint32_t redBits;      ///< 红色通道深度值
        uint32_t greenBits;    ///< 绿色通道深度值
        uint32_t blueBits;     ///< 蓝色通道深度值
        uint32_t alphaBits;    ///< 透明通道深度值
        uint32_t depthBits;    ///< 深度缓冲值
        uint32_t stencilBits;  ///< 模板缓冲区深度
        uint32_t msaaSamples;  ///< MSAA采样
        uint32_t screenWidth;  ///< 场景宽度
        uint32_t screenHeight; ///< 场景高度
        const char *appName;   ///< 名称

        GfxConfiguration(uint32_t r = 8, uint32_t g = 8, uint32_t b = 8, uint32_t a = 8,
                         uint32_t depth = 24, uint32_t stencil = 0, uint32_t mass = 0,
                         uint32_t w = 1920, uint32_t h = 1080, char *name = "PhantomEngine")
        {
        }
        friend std::wostream &operator<<(std::wostream &out, const GfxConfiguration &conf)
        {
            out << "Application Name :" << conf.appName << std::endl;
            out << "GfxConfiguration:"
                << " R:" << conf.redBits << " G:" << conf.greenBits << " B:" << conf.blueBits << " A:" << conf.alphaBits << " D:" << conf.depthBits << " S:" << conf.stencilBits << " M:" << conf.msaaSamples << " W:" << conf.screenWidth << " H:" << conf.screenHeight << std::endl;
            return out;
        }
    };
}
