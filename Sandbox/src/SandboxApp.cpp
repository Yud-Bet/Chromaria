#include <Chromaria.h>

class ExampleLayer : public Chromaria::Layer
{
public:
	ExampleLayer() : Layer("Example") {}

	void OnUpdate() override
	{
		if (Chromaria::Input::IsKeyPressed(CM_KEY_TAB))
			CM_TRACE("Tab key is pressed!");
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