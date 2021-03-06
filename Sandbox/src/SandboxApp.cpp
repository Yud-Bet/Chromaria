#include <Chromaria.h>
#include <Chromaria/Core/EntryPoint.h>

#include <imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Sandbox2D.h" 

class ExampleLayer : public Chromaria::Layer
{
public:
	ExampleLayer() : Layer("Example"), m_CameraController(16.0f/9.0f, true)
	{
		m_VertexArray = Chromaria::VertexArray::Create();

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.9f, 0.6f, 0.06f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.9f, 0.4f, 0.04f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.9f, 0.2f, 0.02f, 1.0f
		};

		Chromaria::Ref<Chromaria::VertexBuffer> vertexBuffer = Chromaria::VertexBuffer::Create(vertices, sizeof(vertices));

		Chromaria::BufferLayout layout = {
			{ Chromaria::ShaderDataType::Float3, "a_Position" },
			{ Chromaria::ShaderDataType::Float4, "a_Color" }
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		unsigned int indices[3] = { 0, 1, 2 };
		Chromaria::Ref<Chromaria::IndexBuffer> indexBuffer = Chromaria::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA = Chromaria::VertexArray::Create();

		float squareVertices[4 * 5] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		vertexBuffer = Chromaria:: VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		vertexBuffer->SetLayout({
			{ Chromaria::ShaderDataType::Float3, "a_Position" },
			{ Chromaria::ShaderDataType::Float2, "a_TexCoord" }
			});
		m_SquareVA->AddVertexBuffer(vertexBuffer);

		unsigned int squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		indexBuffer = Chromaria::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
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

		m_Shader = Chromaria::Shader::Create("VertexPosColor", vertexSrc, fragmentSrc);

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

		m_FlatColorShader = Chromaria::Shader::Create("FlatColor", flatColorShaderVertexSrc, flatColorShaderFragmentSrc);

		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

		m_Texture = Chromaria::Texture2D::Create("assets/textures/Checkerboard.png");
		m_EliteriaTexture = Chromaria::Texture2D::Create("assets/textures/Eliteria.png");

		textureShader->Bind();
		textureShader->SetInt("u_Texture", 0);
	}

	void OnUpdate(Chromaria::Timestep timestep) override
	{
		m_CameraController.OnUpdate(timestep);

		Chromaria::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Chromaria::RenderCommand::Clear();

		Chromaria::Renderer::BeginScene(m_CameraController.GetCamera());

		static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		m_FlatColorShader->Bind();
		m_FlatColorShader->SetFloat3("u_Color", m_SquareColor);
		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Chromaria::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}

		auto textureShader = m_ShaderLibrary.Get("Texture");
		m_Texture->Bind();
		Chromaria::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.0f)));
		m_EliteriaTexture->Bind();
		Chromaria::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.0f)));

		//Chromaria::Renderer::Submit(m_Shader, m_VertexArray);

		Chromaria::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit4("Square color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(Chromaria::Event& e) override
	{
		m_CameraController.OnEvent(e);
	}
private:
	Chromaria::ShaderLibrary m_ShaderLibrary;
	Chromaria::Ref<Chromaria::Shader> m_Shader;
	Chromaria::Ref<Chromaria::VertexArray> m_VertexArray;

	Chromaria::Ref<Chromaria::Shader> m_FlatColorShader;
	Chromaria::Ref<Chromaria::VertexArray> m_SquareVA;

	Chromaria::Ref<Chromaria::Texture2D> m_Texture, m_EliteriaTexture;

	Chromaria::OrthographicCameraController m_CameraController;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};

class Sandbox : public Chromaria::Application
{
public:
	Sandbox()
	{
		// PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}
	~Sandbox() {}
};

Chromaria::Application* Chromaria::CreateApplication()
{
	return new Sandbox();
}