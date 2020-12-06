#pragma once
#include "Rebelle/Renderer/RendererAPI.h"
#include "glad/glad.h"

namespace Rebelle {
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
	};
}