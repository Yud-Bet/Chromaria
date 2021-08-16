#pragma once

#include "Chromaria/Layer.h"

#include "Chromaria/Events/ApplicationEvent.h"
#include "Chromaria/Events/KeyEvent.h"
#include "Chromaria/Events/MouseEvent.h"

namespace Chromaria {

	class CHROMARIA_API ImGuiLayer : public Layer
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