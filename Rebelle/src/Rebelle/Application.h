#pragma once

#include "Core.h"
#include "Window.h"
#include "Rebelle/LayerStack.h"
#include "Rebelle/Events/Event.h"
#include "Rebelle/Events/ApplicationEvent.h"

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
	private:
		bool OnWindowClosed(WindowCloseEvent& e);
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	};

	//to be defined in client
	Application* CreateApplication();
}

