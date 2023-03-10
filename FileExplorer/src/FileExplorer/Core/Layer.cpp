#include "feospch.h"

#include "FileExplorer/Core/Layer.h"


namespace FEOS
{
    LayerStack::~LayerStack()
    {
        for(Layer* layer : m_Layers)
        {
            layer->OnDetach();
            delete layer;
        }
    }

    void LayerStack::PushLayer(Layer* layer)
    {
        m_Layers.emplace(m_Layers.begin() + m_LayersCount, layer);
        ++m_LayersCount;
    }

    void LayerStack::PushOverlay(Layer* overlay)
    {
        m_Layers.emplace_back(overlay);
    }

    void LayerStack::PopLayer(Layer* layer)
    {
        auto it = std::find(m_Layers.begin(), m_Layers.begin() + m_LayersCount, layer);

        if (it == m_Layers.begin() + m_LayersCount)
            return;

        layer->OnDetach();
        m_Layers.erase(it);
        --m_LayersCount;
    }

    void LayerStack::PopOverlay(Layer* overlay)
    {
        auto it = std::find(m_Layers.begin() + m_LayersCount, m_Layers.end(), overlay);

        if (it == m_Layers.end())
            return;

        overlay->OnDetach();
        m_Layers.erase(it);
    }
}
