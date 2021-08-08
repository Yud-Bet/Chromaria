#include <Chromaria.h>

class Sandbox : public Chromaria::Application
{
public:
	Sandbox() {}
	~Sandbox() {}
};

Chromaria::Application* Chromaria::CreateApplication()
{
	return new Sandbox();
}