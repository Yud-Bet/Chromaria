#pragma once

#include "Chromaria/Core/Layer.h"

#include "Chromaria/Events/ApplicationEvent.h"
#include "Chromaria/Events/KeyEvent.h"
#include "Chromaria/Events/MouseEvent.h"

namespace Chromaria {

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};

}