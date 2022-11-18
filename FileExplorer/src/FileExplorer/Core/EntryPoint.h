#pragma once

#include "FileExplorer/Core/Application.h"


#ifdef FILE_EXPLORER_WINDOWS_PLATFOMR


// export Explorer::Application* Explorer::CreateApplication();

int main(int argc, char** argv)
{
    auto app = Explorer::CreateApplication();
    app->run();
    delete app;
}


#endif // FILE_EXPLORER_WINDOWS_PLATFOMR