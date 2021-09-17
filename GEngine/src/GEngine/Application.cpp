#include "GEpch.h"
#include "Application.h"
#include "Events/ApplicationEvent.h"


namespace GEngine {

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
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
}
