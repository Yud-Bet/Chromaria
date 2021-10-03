#pragma once

#ifdef CM_PLATFORM_WINDOWS

extern Chromaria::Application* Chromaria::CreateApplication();

int main(int argc, char** argv)
{
	Chromaria::Log::Init();
	CM_CORE_WARN("Hello");
	CM_FATAL("Bonjour {0}", 3);

	auto app = Chromaria::CreateApplication();
	app->Run();
	delete app;
}

#endif