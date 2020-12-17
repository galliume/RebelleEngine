#pragma once

#include "Core.h"
#include "Window.h"

#include "Rebelle/Core/TimeStep.h"
#include "Rebelle/LayerStack.h"
#include "Rebelle/Events/Event.h"
#include "Rebelle/Events/ApplicationEvent.h"
#include "Rebelle/ImGui/ImGuiLayer.h"

namespace Rebelle {

	class Application
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
	private:		
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
		static Application* s_Instance;
		float m_LastFrameTime = 0.0f;
	};

	//to be defined in client
	Application* CreateApplication();
}