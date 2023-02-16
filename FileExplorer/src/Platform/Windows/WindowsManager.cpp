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
            allFilesInDirectory.push_back(ParseFile(dirPath / file->d_name));
            // allFilesInDirectory.push_back(direntToFile(dirPath / file->d_name));

        closedir(searchedDir);
        return allFilesInDirectory;
    }

    File WindowsManager::GetFileByName(const Path& fileName, bool recursive) const
    {
        File targetFile = ParseFile(GetCurrentPath() / fileName);

        if (targetFile.type != FileType::NotFound || recursive == false)
            return targetFile;

        DIR* searchedDir = opendir(GetCurrentPath().string().c_str());
        FEOS_EXPLORER_ASSERT(searchedDir == nullptr, "Could not Opne the Directory");
        seekdir(searchedDir, 2); // skipping "." and ".."

        for (dirent* file = readdir(searchedDir); file != nullptr; file = readdir(searchedDir))
        {
            Path recursiveFilePath = GetCurrentPath() / file->d_name;
            if (FileType::Folder == MachFilesystemFileTypeToFEOSFileType(fs::status(recursiveFilePath)))
            {
                targetFile = GetFileByName(Path(file->d_name) / fileName, recursive);
                if (targetFile.type != FileType::NotFound)
                    break;
            }
        }

        closedir(searchedDir);
        return targetFile;
    }

        
    File WindowsManager::CreateFile_(const Path& fileName) const 
    {
        Path filePath = GetCurrentPath() / fileName;

        HANDLE h = CreateFile(
            filePath.string().c_str(),
            GENERIC_READ | GENERIC_WRITE,
            FILE_SHARE_VALID_FLAGS,
            nullptr,
            CREATE_NEW,
            FILE_ATTRIBUTE_NORMAL,
            nullptr
        );

        if (h == INVALID_HANDLE_VALUE)
            return InvalideFile();
        
        CloseHandle(h);
        return File{ FileType::File, false, false, true, 0, fileName.string(), filePath };
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
        Path newFileLocation = movedFilePath / file.name;

        WINBOOL succeds = MoveFile(file.path.string().c_str(), newFileLocation.string().c_str());
        
        if (succeds == true)
        {
            file.path = newFileLocation;
        }
    }

    void WindowsManager::MoveFolder(File& folder, const Path& movedFolderPath) const
    {

    }


    void WindowsManager::CopyFile_(const File& file, const Path& copyFilePath) const
    {
        Path copyFileLocation = copyFilePath / file.name;

        if (file.path == copyFileLocation)
        {
            WIN32_FIND_DATA data;
            GET_FILEEX_INFO_LEVELS fileExInfo;
            WINBOOL nthCopyExists;

            int filesWithSameName = 1;
            std::stringstream copyState(file.path.stem().string());
            copyState << " - Copy";

            do
            {
                std::stringstream currentCopyIteration(copyState.str());
                if (filesWithSameName != 1)
                    currentCopyIteration << " (" << filesWithSameName << ")";
                if (!file.path.extension().empty())
                    currentCopyIteration << file.path.extension();

                FEOS_LOG_DEBUG("Looking for {} copy of {}", filesWithSameName, currentCopyIteration.str());
                nthCopyExists = GetFileAttributesEx(currentCopyIteration.str().c_str(), fileExInfo, &data);
            }
            while (nthCopyExists != INVALID_FILE_ATTRIBUTES);
        }

        WINBOOL succeds = CopyFile(file.path.string().c_str(), copyFileLocation.string().c_str(), TRUE);
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


    // Not needed righ now
    File WindowsManager::direntToFile(const Path& direntPath) const
    {
        DWORD attributes = GetFileAttributes(direntPath.string().c_str());

        FileType type = MachFilesystemFileTypeToFEOSFileType(fs::status(direntPath));
        bool system = attributes & FILE_ATTRIBUTE_SYSTEM;
        bool readonly = attributes & FILE_ATTRIBUTE_READONLY;
        bool visible = attributes & FILE_ATTRIBUTE_HIDDEN;
        uint32_t size = type != FileType::Folder ? fs::file_size(direntPath) : 0;

        return File{ type, system, readonly, visible, size, direntPath.filename().string(), direntPath };
    }

    File WindowsManager::ParseFile(const Path& filePath) const
    {
        WIN32_FIND_DATA data;
        GET_FILEEX_INFO_LEVELS fileExInfo;
        
        WINBOOL foundAttrib = GetFileAttributesEx(filePath.string().c_str(), fileExInfo, &data);

        if (foundAttrib == INVALID_FILE_ATTRIBUTES)
        {
            FEOS_LOG_WARN("Could not find file: {}", filePath);
            return InvalideFile();
        }
        
        LARGE_INTEGER size = {{ data.nFileSizeLow, (LONG)data.nFileSizeHigh }};
        FileType type = MachWindowsAttributeToFEOSFileType(data.dwFileAttributes);
        bool system = data.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM;
        bool readonly = data.dwFileAttributes & FILE_ATTRIBUTE_READONLY;
        bool visible = data.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN;
        
        // FindClose(file);
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
        FEOS_LOG_WARN("Unknown filesystem type: {}", (int)filesystemType);
        return FileType::Unknown;
    }

    static FileType MachWindowsAttributeToFEOSFileType(DWORD attribute)
    {
        if (attribute & (FILE_ATTRIBUTE_ARCHIVE | FILE_ATTRIBUTE_NORMAL))
            return FileType::File;
        if (attribute & FILE_ATTRIBUTE_DIRECTORY)
            return FileType::Folder;
        FEOS_LOG_WARN("Unknow windows file type {}", attribute);
        return FileType::Unknown;
    }

    static File InvalideFile()
    {
        return File{ FileType::NotFound, false, true, false, 0, "", "" };
    }
}