#pragma once

// ===================================================
// [基类] RenderPass - 渲染通道基类
// 职责：定义渲染通道的统一接口，所有 Pass 子类继承此类
// 子类：
//   StencilPass  【Step03.2】模板测试描边
//   ModelPass    【Step03.1】模型+光照渲染
//   LightPass    【Step03.4】灯光立方体
//   AlphaPass    【Step03.3】Alpha 混合/透明度
// ===================================================

class RenderPass
{
public:
    virtual void Setup()    {}
    virtual void Execute()  {}
    virtual void Cleanup()  {}
    virtual ~RenderPass() = default;
};
