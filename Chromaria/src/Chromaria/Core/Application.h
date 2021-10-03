#pragma once

#include "Core.h"

#include "Window.h"
#include "Chromaria/Core/LayerStack.h"
#include "Chromaria/Events/ApplicationEvent.h"
#include "Chromaria/Core/Timestep.h"

#include "Chromaria/ImGui/ImGuiLayer.h"

#include "Chromaria/Renderer/Shader.h"
#include "Chromaria/Renderer/Buffer.h"
#include "Chromaria/Renderer/VertexArray.h"
#include "Chromaria/Renderer/OrthographicCamera.h"

namespace Chromaria {

	class CHROMARIA_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_IsRunning = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;
	private:
		static Application* s_Instance;
	};

	Application* CreateApplication();
}