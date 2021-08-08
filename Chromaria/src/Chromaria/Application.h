#pragma once

#include "Core.h"

namespace Chromaria {

	class CHROMARIA_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	Application* CreateApplication();
}