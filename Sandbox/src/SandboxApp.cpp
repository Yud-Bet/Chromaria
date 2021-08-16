#include <Chromaria.h>

class ExampleLayer : public Chromaria::Layer
{
public:
	ExampleLayer() : Layer("Example") {}

	void OnUpdate() override
	{
		CM_INFO("ExampleLayer::Update");
	}

	void OnEvent(Chromaria::Event& e) override
	{
		CM_TRACE(e);
	}
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