#include "Application.h"

#include "Events/ApplicationEvent.h"
#include "Log.h"
#include <iostream>

namespace Chromaria {
	Application::Application()
	{
	}
	Application::~Application()
	{
	}
	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		CM_INFO(e);
		while (true);
	}
}