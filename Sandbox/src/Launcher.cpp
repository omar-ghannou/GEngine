#include <GEngine.h>

class Launcher : public GEngine::Application 
{
public:
	Launcher() {

	}
	~Launcher() {

	}
};

GEngine::Application* GEngine::CreateApplication() {
	return new Launcher();
}