#define ENTRY_POINT
#include <FileExplorer.h>

namespace FEOS
{
    class ProgramClinet : public Application
    {
    public:
        ProgramClinet(FileExplorerSpecifications spec)
            : Application(spec)
        {

        }

        ~ProgramClinet()
        {

        }

    private:

    };

    Application* CreateApplication(FileExplorerCommandLineArgs args)
    {
        FileExplorerSpecifications spec = { "File Explorer", "", args };
        
        return new ProgramClinet(spec);
    }
}