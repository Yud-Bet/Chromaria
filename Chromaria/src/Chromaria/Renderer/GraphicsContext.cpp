#include "cmpch.h"
#include "Chromaria/Renderer/GraphicsContext.h"

#include "Chromaria/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace Chromaria {

	Scope<GraphicsContext> GraphicsContext::Create(void* window)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:	CM_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:	return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
		}

		CM_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}
