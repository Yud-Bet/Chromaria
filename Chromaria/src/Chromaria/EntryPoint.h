#pragma once

#ifdef CM_PLATFORM_WINDOWS

extern Chromaria::Application* Chromaria::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Chromaria::CreateApplication();
	app->Run();
	delete app;
}

#endif