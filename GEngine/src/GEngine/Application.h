#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Window.h"

namespace GEngine {


	class GE_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
	private:
		void OnEvent(Event& e);
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	//Need to be defined in the CLIENT Side
	Application* CreateApplication();

}

