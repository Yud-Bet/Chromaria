#pragma once

#ifdef CM_PLATFORM_WINDOWS

extern Chromaria::Application* Chromaria::CreateApplication();

int main(int argc, char** argv)
{
	Chromaria::Log::Init();

	CM_PROFILE_BEGIN_SESSION("Startup", "ChromariaProfile-Startup.json");
	auto app = Chromaria::CreateApplication();
	CM_PROFILE_END_SESSION();

	CM_PROFILE_BEGIN_SESSION("Runtime", "ChromariaProfile-Runtime.json");
	app->Run();
	CM_PROFILE_END_SESSION();

	CM_PROFILE_BEGIN_SESSION("Shutdown", "ChromariaProfile-Shutdown.json");
	delete app;
	CM_PROFILE_END_SESSION();
}

#endif