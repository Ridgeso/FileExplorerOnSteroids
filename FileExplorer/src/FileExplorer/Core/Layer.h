#pragma once

#include "feospch.h"

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

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);
        void PopLayer(Layer* layer);
        void PopOverlay(Layer* overlay);

        const std::vector<Layer*>& GetStack() const { return m_Layers; }

    private:
        std::vector<Layer*>::iterator LayerPosition(Layer* layer);

    private:
        std::vector<Layer*> m_Layers;
        uint32_t m_LayersCount = 0;
    };
}
