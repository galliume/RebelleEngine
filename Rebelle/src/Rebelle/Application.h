#pragma once

#include "Core.h"
#include "Window.h"
#include "Rebelle/LayerStack.h"
#include "Rebelle/Events/Event.h"
#include "Rebelle/Events/ApplicationEvent.h"
#include "Rebelle/ImGui/ImGuiLayer.h"
#include "Rebelle/Renderer/Shader.h"
#include "Rebelle/Renderer/Buffer.h"
#include "Rebelle/Renderer/VertexArray.h"
#include "Rebelle/Renderer/OrthographicCamera.h"

namespace Rebelle {

	class REBELLE_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClosed(WindowCloseEvent& e);
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
		static Application* s_Instance;


		std::shared_ptr<Shader>m_Shader2;
		std::shared_ptr<VertexArray>m_SquareVertexArray;

		std::shared_ptr<Shader>m_Shader;
		std::shared_ptr<VertexArray>m_VertexArray;

		OrthographicCamera m_Camera;
	};

	//to be defined in client
	Application* CreateApplication();
}