#pragma once
#include <glad/glad.h>

// ===================================================
// RenderTarget - 渲染目标（帧缓冲 FBO）
// 封装帧缓冲对象，支持离屏渲染
// ===================================================
class RenderTarget
{
public:
	unsigned int width  = 1920;
	unsigned int height = 1080;

	RenderTarget()
	{
		glGenFramebuffers(1, &FBO);
		glBindFramebuffer(GL_FRAMEBUFFER, FBO);

		glGenTextures(1, &TEX);
		glBindFramebuffer(GL_TEXTURE_2D, TEX);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}

	void useFBO()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	}

	void useDiffuseFbo()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void delFBO()
	{
		glDeleteFramebuffers(1, &FBO);
	}

private:
	unsigned int FBO;
	unsigned int TEX;
};