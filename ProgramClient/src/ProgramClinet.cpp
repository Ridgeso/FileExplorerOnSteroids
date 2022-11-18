#include <FileExplorer.h>
#include <FileExplorer/Core/EntryPoint.h>

namespace Explorer {


    class ProgramClinet : public Application
    {
    public:
        ProgramClinet()
        {

        }

        ~ProgramClinet()
        {

        }

    private:

    };


    Application* CreateApplication()
    {
        return new ProgramClinet();
    }


}