#pragma once

#include <FileExplorer.h>

namespace FEOS
{
    class ViewPort : public Layer
    {
    public:
        ViewPort();
        virtual ~ViewPort() override;

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnUpdate() override;
        virtual void OnUIDraw() override;
        virtual void OnEvent(Event::Event& e) override;

    private:
        bool m_ShouldReloadFiles;
    
        #define NONE_FILE_SELECTED -1
        int32_t m_SelectedFile;
        Files::FileList m_AllFilesInDirectory;

        enum { NoneAction, CopyAction, MoveAction } m_ActionType;
        Files::File m_ActionFile;
    };
}
