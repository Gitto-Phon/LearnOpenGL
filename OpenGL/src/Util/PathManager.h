#pragma once

#include <string>

// ===================================================
// PathManager - 管理资源路径
// ===================================================

namespace Util
{

class PathManager
{
public:
    // 获取着色器根目录
    static const char* GetShaderPath();
    // 获取贴图根目录
    static const char* GetTexturePath();
    // 获取模型根目录
    static const char* GetModelPath();
};

} // namespace Util
