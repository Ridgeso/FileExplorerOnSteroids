#pragma once

#include "FileExplorer/Core/Application.h"


#ifdef FILE_EXPLORER_WINDOWS_PLATFOMR


// export FEOS::Application* FEOS::CreateApplication();

int main(int argc, char** argv)
{
    FEOS::Log::Init();

    auto app = FEOS::CreateApplication({ argc, argv });
    app->Run();
    delete app;

    FEOS::Log::Shutdown();
}


#endif // FILE_EXPLORER_WINDOWS_PLATFOMR