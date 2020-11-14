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

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;
		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};
}