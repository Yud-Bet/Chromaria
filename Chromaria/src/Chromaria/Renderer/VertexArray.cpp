#include "cmpch.h"
#include "Chromaria/Renderer/VertexArray.h"

#include "Chromaria/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Chromaria {

	Ref<VertexArray> VertexArray::Create()
	{
		CM_PROFILE_FUNCTION();

		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:	CM_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:	return CreateRef<OpenGLVertexArray>();
		}

		CM_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}