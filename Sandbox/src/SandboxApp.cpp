#include <Chromaria.h>

#include "imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

class ExampleLayer : public Chromaria::Layer
{
public:
	ExampleLayer() : Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		m_VertexArray.reset(Chromaria::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.9f, 0.6f, 0.06f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.9f, 0.4f, 0.04f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.9f, 0.2f, 0.02f, 1.0f
		};

		Chromaria::Ref<Chromaria::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Chromaria::VertexBuffer::Create(vertices, sizeof(vertices)));

		Chromaria::BufferLayout layout = {
			{ Chromaria::ShaderDataType::Float3, "a_Position" },
			{ Chromaria::ShaderDataType::Float4, "a_Color" }
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		unsigned int indices[3] = { 0, 1, 2 };
		Chromaria::Ref<Chromaria::IndexBuffer> indexBuffer;
		indexBuffer.reset(Chromaria::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Chromaria::VertexArray::Create());

		float squareVertices[4 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		vertexBuffer.reset(Chromaria:: VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		vertexBuffer->SetLayout({
			{Chromaria::ShaderDataType::Float3, "a_Position"}
			});
		m_SquareVA->AddVertexBuffer(vertexBuffer);

		unsigned int squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		indexBuffer.reset(Chromaria::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(indexBuffer);

		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader.reset(Chromaria::Shader::Create(vertexSrc, fragmentSrc));

		std::string flatColorShaderVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0f);
			}
		)";

		m_FlatColorShader.reset(Chromaria::Shader::Create(flatColorShaderVertexSrc, flatColorShaderFragmentSrc));
	}

	void OnUpdate(Chromaria::Timestep timestep) override
	{
		if (Chromaria::Input::IsKeyPressed(CM_KEY_LEFT))
		{
			m_CameraPosition.x -= m_CameraMoveSpeed * timestep;
		}
		else if (Chromaria::Input::IsKeyPressed(CM_KEY_RIGHT))
		{
			m_CameraPosition.x += m_CameraMoveSpeed * timestep;
		}

		if (Chromaria::Input::IsKeyPressed(CM_KEY_DOWN))
		{
			m_CameraPosition.y -= m_CameraMoveSpeed * timestep;
		}
		else if (Chromaria::Input::IsKeyPressed(CM_KEY_UP))
		{
			m_CameraPosition.y += m_CameraMoveSpeed * timestep;
		}

		if (Chromaria::Input::IsKeyPressed(CM_KEY_A))
		{
			m_CameraRotation -= m_CameraRotateSpeed * timestep;
		}
		else if (Chromaria::Input::IsKeyPressed(CM_KEY_D))
		{
			m_CameraRotation += m_CameraRotateSpeed * timestep;
		}

		Chromaria::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Chromaria::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Chromaria::Renderer::BeginScene(m_Camera);

		static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		m_FlatColorShader->Bind();
		std::dynamic_pointer_cast<Chromaria::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);
		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Chromaria::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}

		Chromaria::Renderer::Submit(m_Shader, m_VertexArray);

		Chromaria::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorPicker3("Square color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(Chromaria::Event& e) override
	{
	}
private:
	Chromaria::Ref<Chromaria::Shader> m_Shader;
	Chromaria::Ref<Chromaria::VertexArray> m_VertexArray;

	Chromaria::Ref<Chromaria::Shader> m_FlatColorShader;
	Chromaria::Ref<Chromaria::VertexArray> m_SquareVA;

	Chromaria::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraRotation = 0.0f;
	float m_CameraMoveSpeed = 1.0f;
	float m_CameraRotateSpeed = 10.0f;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};

class Sandbox : public Chromaria::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}
	~Sandbox() {}
};

Chromaria::Application* Chromaria::CreateApplication()
{
	return new Sandbox();
}