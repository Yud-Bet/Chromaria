#pragma once

#include "Chromaria.h"

class Sandbox2D : public Chromaria::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(Chromaria::Timestep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Chromaria::Event& e) override;
private:
	Chromaria::Ref<Chromaria::Shader> m_FlatColorShader;
	Chromaria::Ref<Chromaria::VertexArray> m_SquareVA;

	Chromaria::Ref<Chromaria::Texture2D> m_CheckerboardTexture;

	Chromaria::OrthographicCameraController m_CameraController;

	struct ProfileResult
	{
		const char* Name;
		float Time;
	};

	std::vector<ProfileResult> m_ProfileResults;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};