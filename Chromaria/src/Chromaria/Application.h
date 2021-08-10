#pragma once

#include "Core.h"
#include "Events/ApplicationEvent.h"
#include "Window.h"

namespace Chromaria {

	class CHROMARIA_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_IsRunning = true;
	};

	Application* CreateApplication();
}