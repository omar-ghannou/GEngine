#pragma once
#include "GEpch.h"
#include "GEngine/Core.h"


namespace GEngine {

	//The Events till now are blocking events and get dispatched once occured. may implement advanced strategies 
	// to cover this blocking. as implementing a buffer (queue) to dispatch later from and not process as it occurs
	
	enum class EventType {
		None = 0,
		WindowClosed, WindowResized, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick,AppUpdate,AppRender,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory {
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput = BIT(1),
		EventCategoryKeyboard = BIT(2),
		EventCategoryMouse = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() {return EventType::##type;}\
								virtual EventType GetEventType() const override {return GetStaticType();}\
								virtual const char* GetName() const override { return #type;}


#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override {return category;}
			
	class GE_API Event {
		friend class EventDispatcher;
	public :
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category) {
			return GetCategoryFlags() & category;
		}
	protected :
		bool m_Handled = false;
	};

	class EventDispatcher {

		template<typename T>
		using EventFn = std::function<bool(T&)>;

	public:
		EventDispatcher(Event& event): m_Event(event) {}

		template<typename T>
		bool Dispatch(EventFn<T> m_function) {
			if (m_Event.GetEventType() == T::GetStaticType()) {
				m_Event.m_Handled = m_function(*(T*)&m_Event);
				return true;
			}
			return false;
		}

	private:
		Event& m_Event;

	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e) {
		return os << e.ToString();
	}

}
