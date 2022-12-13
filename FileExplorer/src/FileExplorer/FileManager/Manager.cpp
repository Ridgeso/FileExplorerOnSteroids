#include "feospch.h"

#include "FileExplorer/FileManager/Manager.h"
#include "Platform/Windows/WindowsManager.h"

namespace FEOS::Files
{
    Manager::Manager(const Path& path)
        : m_CurrentPath(path)
    {
    }
    
    Manager::~Manager()
    {
    }

    Local<Manager> Create(const Path& path)
    {
        return CreateLocal<WindowsManager>(path);
    }
}

std::ostream& operator<<(std::ostream& os, const FEOS::Files::File& file)
{
    std::cout << "File[size: " << file.size << ", path: " << file.path << "]" << std::endl;
    return os;
}