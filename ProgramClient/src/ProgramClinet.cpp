#define ENTRY_POINT
#include <FileExplorer.h>

namespace FEOS
{
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