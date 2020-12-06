#include "rblpch.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Rebelle {
	void VertexArray::Bind() const
	{
	}
	void VertexArray::Unbind() const
	{
	}
	void VertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
	}
	void VertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
	}
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			RBL_CORE_FATAL("No API selected");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLVertexArray();
		}

		RBL_CORE_ASSERT(false, "Unknown Renderer API");
		return nullptr;
	}
}