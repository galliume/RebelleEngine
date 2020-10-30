#pragma once

#include "Core.h"

namespace Rebelle {

	class REBELLE_API Application
	{
		public:

			Application();
			virtual ~Application();
			void Run();
	};

	//to be defined in client
	Application* CreateApplication();
}

