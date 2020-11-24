#pragma once

#include "GLFW/glfw3.h"
#include "Rebelle/Renderer/GraphicsContext.h"

namespace Rebelle {
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);
		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};
}