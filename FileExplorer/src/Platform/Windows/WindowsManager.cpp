#include "feospch.h"

#include <windows.h>
#include "Platform/Windows/WindowsManager.h"

#include <filesystem>


namespace FEOS::Files
{
    WindowsManager::WindowsManager(const Path& path)
        : Manager(path)
    {
        FEOS_LOG_INFO("Manager Initialized at path: {}", path);
    }

    WindowsManager::~WindowsManager()
    {
    }

    std::vector<File> WindowsManager::GetAllFilesFromDirectory(const Path& dirPath) const
    {
        return std::vector<File>();
    }

    File WindowsManager::GetFileByName(const Path& fileName) const
    {
        return File{ FileType::None, true, true, 12, "Test.cpp" };
    }

        
    void WindowsManager::CreateFile(const Path& fileName) const 
    {

    }

    void WindowsManager::CreateFolder(const Path& fileName) const 
    {

    }


    void WindowsManager::DeleteFile(const Path& filePath) const
    {

    }

    void WindowsManager::DeleteFolder(const Path& folderPath) const
    {

    }
    

    void WindowsManager::MoveFile(const Path& filePath) const
    {

    }

    void WindowsManager::MoveFolder(const Path& folderPath) const
    {

    }


    void WindowsManager::CopyFile(const Path& filePath) const
    {

    }

    void WindowsManager::CopyFolder(const Path& folderPath) const
    {

    }


    void WindowsManager::RenameFile(const Path& fileName, const Path& renamedFileName) const
    {

    }

    void WindowsManager::RenameFolder(const Path& folderName, const Path& renamedFolderName) const
    {

    }

}