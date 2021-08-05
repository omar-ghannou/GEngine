#pragma once

#include "Event.h"

#include <sstream>

namespace GEngine {

	class GE_API KeyEvent : public Event {

	public:

		inline int GetKeyCode() const { return m_KeyCode; }
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

	protected:

		KeyEvent(int KeyCode) : m_KeyCode(KeyCode) {}
		int m_KeyCode;

	};

	class GE_API KeyPressedEvent : public KeyEvent {
	public:
		KeyPressedEvent(int KeyCode, int repeatCount) : KeyEvent(KeyCode), m_RepeatCount(repeatCount){}

		inline int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyPressedEvent : " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)

	private:
		int m_RepeatCount;

	};

	class GE_API KeyReleasedEvent : public KeyEvent {
	public:
		KeyReleasedEvent(int KeyCode) : KeyEvent(KeyCode) {}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyReleasedEvent : " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)

	};
}