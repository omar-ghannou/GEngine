#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace GEngine {


	class GE_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
	};

	//Need to be defined in the CLIENT Side
	Application* CreateApplication();

}

