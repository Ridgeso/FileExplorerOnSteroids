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
        WindowsManager(const Path& path = ":Libraries:");
        ~WindowsManager();

        FileList GetAllFilesFromDirectory(const Path& dirPath) const override;

        File GetFileByName(const Path& fileName, bool recursive = false) const override;

        void CreateFile_(const Path& fileName = "New File") const override;
        void CreateFolder(const Path& folderName = "New Folder") const override;

        void DeleteFile_(const Path& filePath) const override;
        void DeleteFolder(const Path& folderPath) const override;
        
        void MoveFile_(File& file, const Path& movedFilePath) const override;
        void MoveFolder(File& folder, const Path& movedFolderPath) const override;

        void CopyFile_(const File& file, const Path& copyFilePath) const override;
        void CopyFolder(const File& folder, const Path& copyFolderPath) const override;

        void RenameFile_(const Path& fileName, const Path& renamedFileName) const override;
        void RenameFolder(const Path& folderName, const Path& renamedFolderName) const override;

    private:
        File direntToFile(const Path& direntPath) const;
        File ParsFile(const Path& filePath) const;

    };

    static FileType MachFilesystemFileTypeToFEOSFileType(const fs::file_status filesystemStatus);
    static FileType MachWindowsAttributeToFEOSFileType(DWORD attribute);
}