#pragma once


#ifdef G_PLATFORM_WINDOWS

extern GEngine::Application* GEngine::CreateApplication();

int main(int argc, char** argv) {
	
	auto app = GEngine::CreateApplication();
	app->Run();
	delete app;

}
#else
	#error This version of GEngine only supports Windows
#endif // G_PLATFORM_WINDOWS
