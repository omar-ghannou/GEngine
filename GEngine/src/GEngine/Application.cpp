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

	void Application::Run()
	{
		//for testing purposes
		
		//WindowResizeEvent e(1280, 720);
		//if(e.IsInCategory(EventCategoryApplication))
		//	GE_TRACE(e);
		//if (e.IsInCategory(EventCategoryInput))
		//	GE_TRACE(e);
		//while (true);

		while (m_Running) {
			m_Window->OnUpdate();
		}
	}
	void Application::OnEvent(Event& e)
	{
		GE_CORE_INFO("{0}", e);
	}
}
