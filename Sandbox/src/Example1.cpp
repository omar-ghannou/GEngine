#include <GEngine.h>

class Example1 : public GEngine::Application 
{
public:
	Example1() {

	}
	~Example1() {

	}
};

GEngine::Application* GEngine::CreateApplication() {
	return new Example1();
}