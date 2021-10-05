#include "Sandbox2D.h"

#include <imgui.h>

#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

Sandbox2D::Sandbox2D()
	:Layer("Sandbox2D"), m_CameraController(16.0 / 9, true)
{
}

void Sandbox2D::OnAttach()
{
	
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Chromaria::Timestep ts)
{
	m_CameraController.OnUpdate(ts);

	Chromaria::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Chromaria::RenderCommand::Clear();

	Chromaria::Renderer2D::BeginScene(m_CameraController.GetCamera());
	Chromaria::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, { 0.8f, 0.2f, 0.3f, 1.0f });
	Chromaria::Renderer2D::EndScene();

	/*m_FlatColorShader->Bind();
	std::dynamic_pointer_cast<Chromaria::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);*/
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Setting");
	ImGui::ColorPicker4("Square color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Chromaria::Event& e)
{
	m_CameraController.OnEvent(e);
}