#include "feospch.h"

#include "Platform/Windows/WindowsManager.h"

#include <windows.h>
#include <shlwapi.h>
#include <dirent.h>
#include <filesystem>


namespace FEOS::Files
{
    WindowsManager::WindowsManager(const Path& path)
        : m_CurrentPath(path)
    {
        FEOS_EXPLORER_ASSERT(!m_CurrentPath.empty(), "There is no path to the root!");

        while (m_CurrentPath != m_CurrentPath.root_path() && !DoesPathExists(m_CurrentPath))
            m_CurrentPath = m_CurrentPath.parent_path();

        FEOS_EXPLORER_ASSERT(DoesPathExists(m_CurrentPath), "Root doesn't exists!");

        FEOS_LOG_TRACE("Manager Initialized at path: {}", m_CurrentPath);
    }

    WindowsManager::~WindowsManager()
    {
    }

    FileList WindowsManager::GetAllFilesFromDirectory(const Path& dirPath) const
    {
        FEOS_LOG_INFO("Reading entire folder: {}", dirPath);

        std::string rePrefix = dirPath.string().back() != '\\' ? "\\*" : "*";
        WIN32_FIND_DATA data = {};
        
        HANDLE fileIterator = FindFirstFile((dirPath.string() + rePrefix).c_str(), &data);
        FEOS_EXPLORER_ASSERT(fileIterator != INVALID_HANDLE_VALUE, "Could not Open the Directory");

        if (fileIterator == INVALID_HANDLE_VALUE)
            return FileList();

        FileList allFilesInDirectory = { ParseWindowsFile(data) };
        while (FindNextFile(fileIterator, &data))
            allFilesInDirectory.push_back(ParseWindowsFile(data));

        FindClose(fileIterator);
        return allFilesInDirectory;
    }

    File WindowsManager::GetFileByName(const Path& fileName, bool recursive) const
    {
        // File targetFile = ParseFile(GetCurrentPath() / fileName);

        // if (targetFile.type != FileType::NotFound || recursive == false)
        //     return targetFile;

        File fileFound;
        WIN32_FIND_DATA data = {};
        
        HANDLE searchedFile = FindFirstFile((GetCurrentPath() / fileName).string().c_str(), &data);
        if (searchedFile != INVALID_HANDLE_VALUE)
            fileFound = ParseWindowsFile(data);
        else if (recursive == false)
            fileFound =  InvalideFile();
        else
        {
            WIN32_FIND_DATA directoriesData = {};
            HANDLE directoriesToSearch = FindFirstFile((GetCurrentPath() / fileName).string().c_str(), &directoriesData);
            if (directoriesToSearch != INVALID_HANDLE_VALUE)
            {
                do
                {
                    if (!(directoriesData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
                        continue;
                    Path newSearchedDirectory = Path(std::string(directoriesData.cFileName));
                    fileFound = GetFileByName(newSearchedDirectory, recursive);
                    if (fileFound.type != FileType::NotFound)
                        break;
                }
                while (FindNextFile(directoriesToSearch, &directoriesData));
            }
        }

        FindClose(searchedFile);
        return fileFound;

        // DIR* searchedDir = opendir(GetCurrentPath().string().c_str());
        // FEOS_EXPLORER_ASSERT(searchedDir == nullptr, "Could not Opne the Directory");
        // seekdir(searchedDir, 2); // skipping "." and ".."

        // for (dirent* file = readdir(searchedDir); file != nullptr; file = readdir(searchedDir))
        // {
        //     Path recursiveFilePath = GetCurrentPath() / file->d_name;
        //     if (FileType::Folder == MachFilesystemFileTypeToFEOSFileType(fs::status(recursiveFilePath)))
        //     {
        //         targetFile = GetFileByName(Path(file->d_name) / fileName, recursive);
        //         if (targetFile.type != FileType::NotFound)
        //             break;
        //     }
        // }

        // closedir(searchedDir);
        // return targetFile;
    }

    
    File WindowsManager::CreateFile_(const Path& fileName) const 
    {
        Path filePath = FindNextFreeFileName(GetCurrentPath() / fileName);

        HANDLE h = CreateFile(
            filePath.string().c_str(),
            GENERIC_READ | GENERIC_WRITE,
            FILE_SHARE_READ | FILE_SHARE_READ | FILE_SHARE_DELETE,
            nullptr,
            CREATE_NEW,
            FILE_ATTRIBUTE_NORMAL,
            nullptr
        );

        if (h == INVALID_HANDLE_VALUE)
            return InvalideFile();
        
        CloseHandle(h);
        return File{ FileType::File, false, false, true, 0, filePath.filename().string(), filePath };
    }

    void WindowsManager::CreateFolder(const Path& folderName) const 
    {

    }


    bool WindowsManager::DeleteFile_(const Path& filePath) const
    {
        return DELETION_ERROR;
    }

    bool WindowsManager::DeleteFolder(const Path& folderPath) const
    {
        return DELETION_ERROR;
    }
    

    void WindowsManager::MoveFile_(File& file, const Path& movedFilePath) const
    {
        Path newFileLocation = movedFilePath / file.name;

        bool succeds = MoveFile(file.path.string().c_str(), newFileLocation.string().c_str());
        
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
        bool succeds = CopyFile(file.path.string().c_str(), copyFilePath.string().c_str(), TRUE);
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
        uint64_t size = type != FileType::Folder ? fs::file_size(direntPath) : 0;

        return File{ type, system, readonly, visible, size, direntPath.filename().string(), direntPath };
    }

    File WindowsManager::ParseWindowsFile(const WIN32_FIND_DATA& fileData) const
    {
        Path filePath = Path(std::string(fileData.cFileName));
        
        LARGE_INTEGER size = {{ fileData.nFileSizeLow, (LONG)fileData.nFileSizeHigh }};
        FileType type = MachWindowsAttributeToFEOSFileType(fileData.dwFileAttributes);
        bool system = fileData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM;
        bool readonly = fileData.dwFileAttributes & FILE_ATTRIBUTE_READONLY;
        bool visible = fileData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN;
        
        return File{ type, system, readonly, visible, (uint64_t)size.QuadPart, filePath.filename().string(), filePath };
    }

    File WindowsManager::ParseFile(const Path& filePath) const
    {
        WIN32_FIND_DATA data = {};
        BOOL foundAttrib = GetFileAttributesEx(filePath.string().c_str(), GetFileExMaxInfoLevel, &data);

        if (foundAttrib == FALSE)
        {
            FEOS_LOG_WARN("Could not find file: {}", filePath);
            return InvalideFile();
        }

        return ParseWindowsFile(data);
    }

    static bool DoesPathExists(const Path& path)
    {
        return PathFileExists(path.string().c_str()) == true;
    }

    static Path FindNextFreeFileName(const Path& path)
    {
        FEOS_LOG_INFO("Looking for avaliable name of: {}", path);


        DWORD nthCopyExists = GetFileAttributesA(path.string().c_str());
        if (nthCopyExists == INVALID_FILE_ATTRIBUTES)
            return path;
        
        std::string nextFreeName = path.parent_path().concat("\\").string() + path.stem().string() + "-Copy" + path.extension().string();
        nthCopyExists = GetFileAttributesA(nextFreeName.c_str());
        if (nthCopyExists == INVALID_FILE_ATTRIBUTES)
            return nextFreeName;

        int filesWithSameName = 2;
        std::string copyState = path.stem().string() + "-Copy(";
        std::stringstream copyIteration;

        do
        {
            copyIteration.str("");
            copyIteration.clear();

            copyIteration << copyState;
            copyIteration << filesWithSameName << ")";
            copyIteration << path.extension().string();

            FEOS_LOG_DEBUG("Looking for {} copy of {}", filesWithSameName, copyIteration.str());
            nthCopyExists = GetFileAttributesA((path.parent_path() / copyIteration.str()).string().c_str());

            filesWithSameName++;
        }
        while (nthCopyExists != INVALID_FILE_ATTRIBUTES);

        return path.parent_path() / copyIteration.str();
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
        return File{ FileType::NotFound, false, true, false, 0, "FILE_NOT_FOUND", "" };
    }
}