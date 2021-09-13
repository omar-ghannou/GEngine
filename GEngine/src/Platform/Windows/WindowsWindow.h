#pragma once
#include "GEngine/Window.h"
#include <GLFW/glfw3.h>

namespace GEngine {

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

	private:


	};
}

