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
        SymLink, Block, Character, Fifo, Socket,
        Unknown
    };

    using Path = std::filesystem::path;

    struct File
    {
        FileType type;
        bool readOnly;
        bool visible;
        uint32_t size;
        Path path;
    };

    class Manager
    {
    public:
        Manager(const Path& path);
        virtual ~Manager();

        virtual std::vector<File> GetAllFilesFromDirectory(const Path& dirPath) const = 0;
        std::vector<File> GetAllFiles() const { return GetAllFilesFromDirectory(m_CurrentPath); }

        virtual File GetFileByName(const Path& fileName) const = 0;

        virtual void CreateFile(const Path& fileName) const = 0;
        virtual void CreateFolder(const Path& fileName) const = 0;

        virtual void DeleteFile(const Path& filePath) const = 0;
        virtual void DeleteFolder(const Path& folderPath) const = 0;
        
        virtual void MoveFile(const Path& filePath) const = 0;
        virtual void MoveFolder(const Path& folderPath) const = 0;

        virtual void CopyFile(const Path& filePath) const = 0;
        virtual void CopyFolder(const Path& folderPath) const = 0;

        virtual void RenameFile(const Path& fileName, const Path& renamedFileName) const = 0;
        virtual void RenameFolder(const Path& folderName, const Path& renamedFolderName) const = 0;

        const Path& GetCurrentPath() const { return m_CurrentPath; }
        void SetCurrentPath(const Path& newPath) { m_CurrentPath = newPath; }
        // void SetCurrentPath(Path&& newPath) { m_CurrentPath = newPath; }

    private:
        Path m_CurrentPath;
    };

    Local<Manager> Create(const Path& path);

}

std::ostream& operator<<(std::ostream& os, const FEOS::Files::File& file);