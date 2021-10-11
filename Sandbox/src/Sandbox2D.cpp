#include "Sandbox2D.h"

#include <imgui.h>

#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
	:Layer("Sandbox2D"), m_CameraController(16.0f / 9.0f, true)
{
}

void Sandbox2D::OnAttach()
{
	CM_PROFILE_FUNCTION();
	m_CheckerboardTexture = Chromaria::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach()
{
	CM_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(Chromaria::Timestep ts)
{
	CM_PROFILE_FUNCTION();

	m_CameraController.OnUpdate(ts);

	{
		CM_PROFILE_SCOPE("Render preparation");
		Chromaria::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Chromaria::RenderCommand::Clear();
	}

	{
		CM_PROFILE_SCOPE("Draw call");
		Chromaria::Renderer2D::BeginScene(m_CameraController.GetCamera());
		Chromaria::Renderer2D::DrawQuad({ 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Chromaria::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.5f, 1.0f }, { 0.2f, 0.3f, 1.0f, 1.0f });
		Chromaria::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_CheckerboardTexture, { 0.15f, 0.15f, 0.15f, 1.0f }, 10.0f);
		Chromaria::Renderer2D::EndScene();
	}

	/*m_FlatColorShader->Bind();
	std::dynamic_pointer_cast<Chromaria::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);*/
}

void Sandbox2D::OnImGuiRender()
{
	CM_PROFILE_FUNCTION();

	ImGui::Begin("Setting");
	ImGui::ColorEdit4("Square color", glm::value_ptr(m_SquareColor));

	ImGui::End();
}

void Sandbox2D::OnEvent(Chromaria::Event& e)
{
	m_CameraController.OnEvent(e);
}