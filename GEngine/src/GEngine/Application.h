#pragma once

#include "Core.h"

namespace GEngine {


	class G_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
	};

	Application* CreateApplication();

}

