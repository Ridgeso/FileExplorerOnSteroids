#include "FileExplorer/Core/Log.h"


namespace FEOS
{
    HANDLE Log::Console = GetStdHandle(STD_OUTPUT_HANDLE);

    void Log::Init()
    {
    }

    void Log::Shutdown()
    {
    }
}