#pragma once

#include "GEpch.h"
#include "Core.h"
#include "Events/Event.h"


namespace GEngine {

	struct WindowProps {

		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(std::string& title =  (std::string)"GEngine" , unsigned int width = 1280, unsigned int height = 720) 
			: Title(title) , Width (width), Height(height) {}
	};


	//currently represents Desktop systems, phones has surface not windows
	class GE_API Window {
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;


		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());

	};

}


