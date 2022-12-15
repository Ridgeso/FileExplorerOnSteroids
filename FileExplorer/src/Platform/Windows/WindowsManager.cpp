#include "feospch.h"

#include "Platform/Windows/WindowsManager.h"

#include <windows.h>
#include <dirent.h>
#include <filesystem>


namespace FEOS::Files
{
    WindowsManager::WindowsManager(const Path& path)
        : Manager(path)
    {
        FEOS_LOG_TRACE("Manager Initialized at path: {}", path);

        FileList filesInRoot = GetAllFiles();
        for (File file : filesInRoot)
        {
            FEOS_LOG_TRACE("-- {}", file);
        }
    }

    WindowsManager::~WindowsManager()
    {
    }

    FileList WindowsManager::GetAllFilesFromDirectory(const Path& dirPath) const
    {
        // TODO: Unsave function
        DIR* searchedDir = opendir(dirPath.string().c_str());
        FEOS_EXPLORER_ASSERT(searchedDir != nullptr, "Could not Open the Directory");
        FileList allFilesInDirectory = { };

        for (dirent* file = readdir(searchedDir); file != nullptr; file = readdir(searchedDir))
            allFilesInDirectory.push_back(ParsFile(dirPath / file->d_name));
            // allFilesInDirectory.push_back(direntToFile(dirPath / file->d_name));

        closedir(searchedDir);
        return allFilesInDirectory;
    }

    File WindowsManager::GetFileByName(const Path& fileName, bool recursive) const
    {
        DIR* searchedDir = opendir(GetCurrentPath().string().c_str());
        FEOS_EXPLORER_ASSERT(searchedDir == nullptr, "Could not Opne the Directory")
        File targetFile;

        for (dirent* file = readdir(searchedDir); file != nullptr; file = readdir(searchedDir))
        { 
        }

        closedir(searchedDir);
        return File{ FileType::None, true, true, true, 12, "Test.cpp", "C:\\tmp\\Test.cpp" };
    }

        
    void WindowsManager::CreateFile_(const Path& fileName) const 
    {
        HANDLE h = CreateFile(
            fileName.string().c_str(),
            GENERIC_READ,
            FILE_SHARE_READ  | FILE_SHARE_WRITE,
            nullptr,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            nullptr
        );

        if (h == INVALID_HANDLE_VALUE)
            return;
        
        CloseHandle(h);
    }

    void WindowsManager::CreateFolder(const Path& folderName) const 
    {

    }


    void WindowsManager::DeleteFile_(const Path& filePath) const
    {

    }

    void WindowsManager::DeleteFolder(const Path& folderPath) const
    {

    }
    

    void WindowsManager::MoveFile_(File& file, const Path& movedFilePath) const
    {

    }

    void WindowsManager::MoveFolder(File& folder, const Path& movedFolderPath) const
    {

    }


    void WindowsManager::CopyFile_(const File& file, const Path& copyFilePath) const
    {

    }

    void WindowsManager::CopyFolder(const File& folder, const Path& copyFolderPath) const
    {

    }


    void WindowsManager::RenameFile_(const Path& fileName, const Path& renamedFileName) const
    {

    }

    void WindowsManager::RenameFolder(const Path& folderName, const Path& renamedFolderName) const
    {

    }


    File WindowsManager::direntToFile(const Path& direntPath) const
    {
        // Not needed righ now
        DWORD attributes = GetFileAttributes(direntPath.string().c_str());

        FileType type = MachFilesystemFileTypeToFEOSFileType(fs::status(direntPath));
        bool system = attributes & FILE_ATTRIBUTE_SYSTEM;
        bool readonly = attributes & FILE_ATTRIBUTE_READONLY;
        bool visible = attributes & FILE_ATTRIBUTE_HIDDEN;
        uint32_t size = type != FileType::Folder ? fs::file_size(direntPath) : 0;

        return File{ type, system, readonly, visible, size, direntPath.filename().string(), direntPath };
    }

    File WindowsManager::ParsFile(const Path& filePath) const
    {
        Path path = filePath;

        WIN32_FIND_DATA data;
        HANDLE file = FindFirstFile(path.string().c_str(), &data);

        if (file == INVALID_HANDLE_VALUE)
        {
            FEOS_LOG_WARN("Could not find file: {}", path);
            return File{ FileType::NotFound, false, true, false, 0, "", "" };
        }
        
        LARGE_INTEGER size = {{ data.nFileSizeLow, (LONG)data.nFileSizeHigh }};
        FileType type = MachWindowsAttributeToFEOSFileType(data.dwFileAttributes);
        bool system = data.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM;
        bool readonly = data.dwFileAttributes & FILE_ATTRIBUTE_READONLY;
        bool visible = data.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN;
        
        FindClose(file);
        return File{ type, system, readonly, visible, (uint64_t)size.QuadPart, filePath.filename().string(), filePath };
    }

    static FileType MachFilesystemFileTypeToFEOSFileType(fs::file_status filesystemStatus)
    {
        fs::file_type filesystemType = filesystemStatus.type();
        switch (filesystemType)
        {
            case fs::file_type::not_found:  return FileType::NotFound;
            case fs::file_type::none:       return FileType::None;
            case fs::file_type::regular:    return FileType::File;
            case fs::file_type::directory:  return FileType::Folder;
            case fs::file_type::symlink:    return FileType::Link;
            case fs::file_type::block:      return FileType::Block;
            case fs::file_type::character:  return FileType::Character;
            case fs::file_type::fifo:       return FileType::Fifo;
            case fs::file_type::socket:     return FileType::Socket;
        }
        FEOS_LOG_WARN("Unknown file fype");
        return FileType::Unknown;
    }

    static FileType MachWindowsAttributeToFEOSFileType(DWORD attribute)
    {
        if (attribute & FILE_ATTRIBUTE_NORMAL)
            return FileType::File;
        if (attribute & FILE_ATTRIBUTE_DIRECTORY)
            return FileType::Folder;
        FEOS_LOG_WARN("Unknow file type");
        return FileType::Unknown;
    }
}