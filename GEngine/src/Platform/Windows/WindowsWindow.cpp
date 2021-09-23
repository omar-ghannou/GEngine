
#include "GEpch.h"
#include "WindowsWindow.h"

#include "GEngine/Events/ApplicationEvent.h"
#include "GEngine/Events/MouseEvent.h"
#include "GEngine/Events/KeyEvent.h"



namespace GEngine {

	static bool s_GLFWInitialized = false;

	static void GLFWErrorCallback(int error, const char* description) {
		GE_CORE_ERROR("GLFW Error ({0}) : {1}", error, description);
	}

	Window* Window::Create(const WindowProps& props) {
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::OnUpdate()
	{
		glClearColor(1, 1, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled) {
			glfwSwapInterval(1);
		}
		else {
			glfwSwapInterval(0);
		}
		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.width = props.Width;
		m_Data.height = props.Height;

		GE_CORE_INFO("Creating a Window {0} ({1}, {2})...",m_Data.Title, m_Data.width, m_Data.height);

		if (!s_GLFWInitialized) {
			int success = glfwInit();
			GE_CORE_ASSERT(success, "Could not initialise GLFW");
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		m_Window = glfwCreateWindow((int)m_Data.width, (int)m_Data.height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		//Set GLFW Callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) 
		{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.width = width;
				data.height = height;
				WindowResizeEvent m_event(width,height);
				data.EventCallback(m_event);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				WindowClosedEvent m_event;
				data.EventCallback(m_event);
		});

		glfwSetWindowFocusCallback(m_Window, [](GLFWwindow* window, int focus) 
		{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				if (focus == GLFW_TRUE) {
					WindowFocusEvent m_event;
					data.EventCallback(m_event);
				}
				else {
					WindowFocusLostEvent m_event;
					data.EventCallback(m_event);
				}
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) 
		{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				switch (action) {
					case GLFW_PRESS:
					{
						KeyPressedEvent m_event(key, 0);
						data.EventCallback(m_event);
						break;
					}
					case GLFW_RELEASE:
					{
						KeyReleasedEvent m_event(key);
						data.EventCallback(m_event);
						break;
					}
					case GLFW_REPEAT:
					{
						KeyPressedEvent m_event(key, 1);
						data.EventCallback(m_event);
						break;
					}
				}
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) 
		{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				switch (action) {
					case GLFW_PRESS:
					{
						MouseButtonPressedEvent m_event(button);
						data.EventCallback(m_event);
						break;
					}
					case GLFW_RELEASE:
					{
						MouseButtonReleasedEvent m_event(button);
						data.EventCallback(m_event);
						break;
					}
				}
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
		{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				MouseScrolledEvent m_event((float)xOffset, (float)yOffset);
				data.EventCallback(m_event);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
		{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				MouseMovedEvent m_event((float)xPos, (float)yPos);
				data.EventCallback(m_event);
		});

	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

}
