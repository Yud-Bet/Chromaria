#include "cmpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Chromaria
{



	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		CM_CORE_ASSERTS(windowHandle, "Window handle is null!");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		CM_CORE_ASSERTS(status, "Failed to initialize Glad!");

		CM_CORE_INFO("OpenGl info:");
		CM_CORE_INFO("Vendor: {0}", glGetString(GL_VENDOR));
		CM_CORE_INFO("Renderer: {0}", glGetString(GL_RENDERER));
		CM_CORE_INFO("Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

}