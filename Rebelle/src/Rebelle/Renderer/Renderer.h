#pragma once

#include "Rebelle/Renderer/RendererAPI.h";
#include "RenderCommand.h"

namespace Rebelle {
	class Renderer
	{
	public:
		static void BeginScene();
		static void EndScene();
		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};
}