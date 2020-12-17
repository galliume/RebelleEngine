#pragma once

#include "Rebelle/Core.h"
#include "Rebelle/Events/Event.h"
#include "Rebelle/Core/TimeStep.h"

namespace Rebelle {

	class REBELLE_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(TimeStep timeStep) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; };

	protected:
		std::string m_DebugName;
	};
}