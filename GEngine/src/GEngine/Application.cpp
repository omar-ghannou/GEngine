#include "GEpch.h"
#include "Application.h"
#include "Events/ApplicationEvent.h"


namespace GEngine {

#define BIND_APPLICATION_EVENT_FN(x) std::bind(&Application::x,this,std::placeholders::_1)

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_APPLICATION_EVENT_FN(OnEvent));
	}


	Application::~Application()
	{

	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowClosedEvent>(BIND_APPLICATION_EVENT_FN(OnWindowClose));
#ifdef _DEBUG
		GE_CORE_TRACE("{0}", e);
#endif // DEBUG
	}

	void Application::Run()
	{
		while (m_Running) {
			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowClosedEvent& e) {
		m_Running = false;
		return true;
	}

}
