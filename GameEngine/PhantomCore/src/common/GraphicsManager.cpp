#include "GraphicsManager.h"
#include <iostream>
using namespace std;
namespace Phantom
{
    GraphicsManager::~GraphicsManager()
    {
        cout << "~GraphicsManager" << endl;
    };
    //初始化函数
    int GraphicsManager::Initialize()
    {
        cout << "Initialize" << endl;
        return 0;
    };
    //完成结束函数
    void GraphicsManager::Finalize()
    {
        cout << "Finalize" << endl;
    };
    //跳动帧函数
    void GraphicsManager::Tick()
    {
        cout << "Tick" << endl;
    };
    //绘制单一网格
    void GraphicsManager::DrawSingleMesh()
    {
        std::cout << "DrawSingleMesh" << endl;
    };
}