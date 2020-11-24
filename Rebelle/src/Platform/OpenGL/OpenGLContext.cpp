#include "rblpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include "glad/glad.h"

namespace Rebelle {
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : m_WindowHandle(windowHandle)
	{

	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		RBL_CORE_ASSERT(status, "failed to initialize glad");

		RBL_CORE_INFO("OpenGl renderer:");
		RBL_CORE_INFO("	Vendor: {0}", glGetString(GL_VENDOR));
		RBL_CORE_INFO("	GPU: {0}", glGetString(GL_RENDERER));
		RBL_CORE_INFO("	Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}