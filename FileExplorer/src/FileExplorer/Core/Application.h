#pragma once

#ifndef FILE_EXPLORER_WINDOWS_PLATFOMR
#   error Only windows is supported
#endif

namespace Explorer {

    class Application
    {
    public:
        Application();
        virtual ~Application();

        void run();
    private:

    };

    // To be defined in CLIENT
    Application* CreateApplication();

}