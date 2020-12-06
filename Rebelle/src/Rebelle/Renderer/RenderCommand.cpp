#include "rblpch.h"
#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Rebelle {
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}