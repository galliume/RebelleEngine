#include <Rebelle.h>

class ExampleLayer : public Rebelle::Layer
{
public:
	ExampleLayer() : Layer("Exemple"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f, 0.0f, 0.0f)
	{
		m_VertexArray.reset(Rebelle::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		Rebelle::BufferLayout layout = {
			{ Rebelle::ShaderDataType::Float3, "a_Positon" },
			{ Rebelle::ShaderDataType::Float4, "a_Color" }
		};

		std::shared_ptr<Rebelle::VertexBuffer>vertexBuffer;
		vertexBuffer.reset(Rebelle::VertexBuffer::Create(vertices, sizeof(vertices)));
		vertexBuffer->SetLayout(layout);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<Rebelle::IndexBuffer>indexBuffer;
		indexBuffer.reset(Rebelle::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		m_VertexArray->AddVertexBuffer(vertexBuffer);
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVertexArray.reset(Rebelle::VertexArray::Create());

		float vertices2[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};
		std::shared_ptr<Rebelle::VertexBuffer> squareVB;
		squareVB.reset(Rebelle::VertexBuffer::Create(vertices2, sizeof(vertices2)));

		squareVB->SetLayout({
			{ Rebelle::ShaderDataType::Float3, "a_Positon" }
			});
		m_SquareVertexArray->AddVertexBuffer(squareVB);

		uint32_t indices2[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Rebelle::IndexBuffer> squareIB;
		squareIB.reset(Rebelle::IndexBuffer::Create(indices2, sizeof(indices2) / sizeof(uint32_t)));
		m_SquareVertexArray->SetIndexBuffer(squareIB);

		std::string vertexSrc2 = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			
			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}					
		)";

		std::string fragmentSrc2 = R"(
			#version 330 core

			layout(location = 0) out vec4 color;
			in vec3 v_Position;

			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}					
		)";

		m_Shader2.reset(new Rebelle::Shader(vertexSrc2, fragmentSrc2));

		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			
			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}					
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}					
		)";

		m_Shader.reset(new Rebelle::Shader(vertexSrc, fragmentSrc));
	}

	void OnUpdate(Rebelle::TimeStep timeStep) override
	{		
		RBL_INFO(timeStep);
		if (Rebelle::Input::IsKeyPressed(RBL_KEY_LEFT))
		{
			m_CameraPosition.x += m_CameraSpeed * timeStep;
		}
		else if (Rebelle::Input::IsKeyPressed(RBL_KEY_RIGHT))
		{
			m_CameraPosition.x -= m_CameraSpeed * timeStep;
		}
		
		if (Rebelle::Input::IsKeyPressed(RBL_KEY_UP))
		{
			m_CameraPosition.y -= m_CameraSpeed * timeStep;
		}
		else if (Rebelle::Input::IsKeyPressed(RBL_KEY_DOWN))
		{
			m_CameraPosition.y += m_CameraSpeed * timeStep;
		}

		if (Rebelle::Input::IsKeyPressed(RBL_KEY_Q))
		{
			m_CameraRotation -= m_CameraRotationSpeed * timeStep;
		}
		else if (Rebelle::Input::IsKeyPressed(RBL_KEY_W))
		{
			m_CameraRotation += m_CameraRotationSpeed * timeStep;
		}

		Rebelle::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Rebelle::RenderCommand::Clear();

		m_Camera.SetPostion(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Rebelle::Renderer::BeginScene(m_Camera);

		Rebelle::Renderer::Submit(m_Shader2, m_SquareVertexArray);
		Rebelle::Renderer::Submit(m_Shader, m_VertexArray);

		Rebelle::Renderer::EndScene();
	}

	void OnEvent(Rebelle::Event& event) override
	{

	}

	virtual void OnImGuiRender() override
	{

	}
private:
	std::shared_ptr<Rebelle::Shader>m_Shader2;
	std::shared_ptr<Rebelle::VertexArray>m_SquareVertexArray;

	std::shared_ptr<Rebelle::Shader>m_Shader;
	std::shared_ptr<Rebelle::VertexArray>m_VertexArray;

	Rebelle::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraSpeed = 1.0f;
	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 10.0f;

};

class SandBox : public Rebelle::Application
{
	public:
		SandBox()
		{
			PushLayer(new ExampleLayer());
		}

		~SandBox()
		{

		}

};

Rebelle::Application* Rebelle::CreateApplication()
{
	return new SandBox();
}