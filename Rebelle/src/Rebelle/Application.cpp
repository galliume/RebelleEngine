#include "rblpch.h"
#include "Application.h"

#include "Rebelle/Events/ApplicationEvent.h"
#include "Rebelle/Log.h"

namespace Rebelle {

	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		//test events
		WindowResizeEvent e(1200, 720);

		if (e.IsInCategory(EventCategoryApplication)) 
		{
			RBL_TRACE(e);
		}
		if (e.IsInCategory(EventCategoryInput))
		{
			RBL_TRACE(e);
		}

		while (true) 
		{

		}

	}
}