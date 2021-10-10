#include "cmpch.h"
#include "Chromaria/Renderer/RenderCommand.h"

namespace Chromaria {

	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();

}