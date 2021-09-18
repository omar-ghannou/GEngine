#pragma once
#include "GEngine/Window.h"
#define GLFW_DLL
#include <GLFW/glfw3.h>


namespace GEngine {

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.width; }
		inline unsigned int GetHeight() const override { return m_Data.height; }

		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

	private:

		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

	private:

		GLFWwindow* m_Window;

		struct WindowData {
			std::string Title;
			unsigned int width, height;
			bool VSync = false;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;

	};
}

