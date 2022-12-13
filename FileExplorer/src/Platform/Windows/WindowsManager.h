#pragma once

#include "FileExplorer/Core/Base.h"

#include "FileExplorer/FileManager/Manager.h"

#include <string>
#include <vector>

namespace FEOS::Files
{
    class WindowsManager : public Manager
    {
    public:
        WindowsManager(const Path& path);
        ~WindowsManager();

        std::vector<File> GetAllFilesFromDirectory(const Path& dirPath) const override;

        File GetFileByName(const Path& fileName) const override;

        void CreateFile(const Path& fileName) const override;
        void CreateFolder(const Path& fileName) const override;

        void DeleteFile(const Path& filePath) const override;
        void DeleteFolder(const Path& folderPath) const override;
        
        void MoveFile(const Path& filePath) const override;
        void MoveFolder(const Path& folderPath) const override;

        void CopyFile(const Path& filePath) const override;
        void CopyFolder(const Path& folderPath) const override;

        void RenameFile(const Path& fileName, const Path& renamedFileName) const override;
        void RenameFolder(const Path& folderName, const Path& renamedFolderName) const override;

    private:
    };
}