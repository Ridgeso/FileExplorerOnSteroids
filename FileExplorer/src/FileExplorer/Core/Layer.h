#pragma once
#include <string>
#include <cstdint>
#include <vector>

#include "FileExplorer/Events/Event.h"

namespace FEOS
{
    class Layer
    {       
    public:
        Layer(const std::string& name = "Layer")
            : m_Name(name)
        { }
        virtual ~Layer() = default;

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate() {}
        virtual void OnUIDraw() {}
        virtual void OnEvent(Event::Event& e) {}

        const std::string& GetName() { return m_Name; }
    private:
        std::string m_Name;
    };

    class LayerStack
    {
    public:
        LayerStack() = default;
        ~LayerStack();

        using Stack = std::vector<Layer*>;

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);
        void PopLayer(Layer* layer);
        void PopOverlay(Layer* overlay);

        const Stack& GetStack() const { return m_Layers; }

        Stack::iterator begin() { return m_Layers.begin(); }
		Stack::iterator end() { return m_Layers.end(); }
		Stack::reverse_iterator rbegin() { return m_Layers.rbegin(); }
		Stack::reverse_iterator rend() { return m_Layers.rend(); }

		Stack::const_iterator begin() const { return m_Layers.begin(); }
		Stack::const_iterator end()	const { return m_Layers.end(); }
		Stack::const_reverse_iterator rbegin() const { return m_Layers.rbegin(); }
		Stack::const_reverse_iterator rend() const { return m_Layers.rend(); }

    private:
        Stack m_Layers;
        uint32_t m_LayersCount = 0;
    };
}
