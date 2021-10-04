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
	m_SquareVA = Chromaria::VertexArray::Create();

	float squareVertices[4 * 5] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

	Chromaria::Ref<Chromaria::VertexBuffer> squareVB;
	squareVB = Chromaria::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
	squareVB->SetLayout({
		{ Chromaria::ShaderDataType::Float3, "a_Position" },
		});
	m_SquareVA->AddVertexBuffer(squareVB);

	Chromaria::Ref<Chromaria::IndexBuffer> squareIB;
	unsigned int squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	squareIB = Chromaria::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
	m_SquareVA->SetIndexBuffer(squareIB);

	m_FlatColorShader = Chromaria::Shader::Create("assets/shaders/FlatColor.glsl");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Chromaria::Timestep ts)
{
	m_CameraController.OnUpdate(ts);

	Chromaria::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Chromaria::RenderCommand::Clear();

	Chromaria::Renderer::BeginScene(m_CameraController.GetCamera());

	m_FlatColorShader->Bind();
	std::dynamic_pointer_cast<Chromaria::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);
	Chromaria::Renderer::Submit(m_FlatColorShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.0f)));

	Chromaria::Renderer::EndScene();
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