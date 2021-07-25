#pragma once


#ifdef GE_PLATFORM_WINDOWS

extern GEngine::Application* GEngine::CreateApplication();

int main(int argc, char** argv) {
	
	GEngine::Log::Init();
	GE_CORE_WARN("Engine has been initialized");
	int state = 0;
	GE_INFO("Application has been started, state = {0}",state);

	auto app = GEngine::CreateApplication();
	app->Run();
	delete app;

}
#else
	#error This version of GEngine only supports Windows
#endif // GE_PLATFORM_WINDOWS
