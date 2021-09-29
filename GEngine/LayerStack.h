#pragma once

#include "GEngine/Core.h"
#include "Layer.h"

namespace GEngine
{
	typedef std::vector<Layer*> Layers;

	class GE_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		inline Layers::iterator begin() { return m_Layers.begin(); }
		inline Layers::iterator end() { return m_Layers.end(); }

	private:
		Layers m_Layers;
		Layers::iterator m_LayerInsert;

	};
}


