#pragma once

#include "FileExplorer/Core/Base.h"

#include <iostream>
#include <string>
#include <vector>

namespace FEOS::Files
{
    enum class FileType
    {
        NotFound = -1, None = 0, 
        File, Folder,
        Link, Block, Character, Fifo, Socket, Disk,
        Unknown
    };

    namespace fs = std::filesystem;
    using Path = fs::path;

    struct File
    {
        FileType type;
        bool system;
        bool readonly;
        bool visible;
        uint64_t size;
        std::string name;
        Path path;
    };

    using FileList = std::vector<File>;

    class Manager
    {
    public:
        Manager(const Path& path);
        virtual ~Manager();

        virtual FileList GetAllFilesFromDirectory(const Path& dirPath) const = 0;
        FileList GetAllFiles() const { return GetAllFilesFromDirectory(m_CurrentPath); }

        virtual File GetFileByName(const Path& fileName, bool recursive) const = 0;

        virtual void CreateFile_(const Path& fileName) const = 0;
        virtual void CreateFolder(const Path& folderName) const = 0;

        virtual void DeleteFile_(const Path& filePath) const = 0;
        virtual void DeleteFolder(const Path& folderPath) const = 0;
        
        virtual void MoveFile_(File& file, const Path& movedFilePath) const = 0;
        virtual void MoveFolder(File& folder, const Path& movedFolderPath) const = 0;

        virtual void CopyFile_(const File& file, const Path& copyFilePath) const = 0;
        virtual void CopyFolder(const File& fifolderle, const Path& copyFolderPath) const = 0;

        virtual void RenameFile_(const Path& fileName, const Path& renamedFileName) const = 0;
        virtual void RenameFolder(const Path& folderName, const Path& renamedFolderName) const = 0;

        const Path& GetCurrentPath() const { return m_CurrentPath; }
        void SetCurrentPath(const Path& newPath) { m_CurrentPath = newPath; }

    private:
        Path m_CurrentPath;
    };

    Local<Manager> Create(const Path& path);

    std::ostream& operator<<(std::ostream& os, const File& file);
}
