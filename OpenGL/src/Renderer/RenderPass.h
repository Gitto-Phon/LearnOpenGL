#pragma once

// ===================================================
// RenderPass - 渲染通道基类
// 提供 Setup / Execute / Cleanup 三个阶段的虚函数接口
// ===================================================

class RenderPass
{
public:
    virtual void Setup()    {}
    virtual void Execute()  {}
    virtual void Cleanup()  {}
    virtual ~RenderPass() = default;
};
