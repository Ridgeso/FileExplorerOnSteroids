#include "feospch.h"

#include "FileExplorer/FileManager/Manager.h"
#include "Platform/Windows/WindowsManager.h"

namespace FEOS::Files
{
    Manager::~Manager()
    {
    }

    Local<Manager> Create(const Path& path)
    {
        return CreateLocal<WindowsManager>(path);
    }

    std::ostream& operator<<(std::ostream& os, const File& file)
    {
        os << "File \"" << file.name << "\"[size: " << file.size << ", path: " << file.path.string() << "]" << std::endl;
        return os;
    }
}
