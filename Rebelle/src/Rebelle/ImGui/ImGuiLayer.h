#pragma once

#include "Rebelle/Layer.h"
#include "Rebelle/Events/ApplicationEvent.h"
#include "Rebelle/Events/MouseEvent.h"
#include "Rebelle/Events/KeyEvent.h"

namespace  Rebelle {

	class REBELLE_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& event);
	private:
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& event);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& event);
		bool OnMouseMovedEvent(MouseMovedEvent& event);
		bool OnMouseScrolledEvent(MouseScrolledEvent& event);
		bool OnKeyPressedEvent(KeyPressedEvent& event);
		bool OnKeyReleased(KeyReleasedEvent& event);
		bool OnKeyTypedEvent(KeyTypedEvent& event);
		bool OnWindowResizedEvent(WindowResizeEvent& event);
	private:
		float m_Time = 0.0f;
	};
}