#pragma once

#include "Chromaria/Renderer/OrthographicCamera.h"
#include "Chromaria/Core/Timestep.h"

#include "Chromaria/Events/ApplicationEvent.h"
#include "Chromaria/Events/MouseEvent.h"

namespace Chromaria {

	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }

		void SetZoomLevel(float level) { m_ZoomLevel = level; }
		float GetZoomLevel() const { return m_ZoomLevel; }
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		OrthographicCamera m_Camera;

		bool m_Rotation;

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0;
		float m_CameraTranslationSpeed = 1.0f, m_CameraRotationSpeed = 5.0f;
	};

}