#pragma once

#include "FileExplorer/Events/Event.h"


namespace FEOS::Event
{
    class ChangePath : public Event
    {
    public:
        ChangePath(const char* path)
            : m_Path(path)
        { }

        EVENT_CLASS_TYPE(ChangePath)
        EVENT_CLASS_CATEGORY(FileSystemCategory)

        EVENT_TO_STRING("ChangePathEvent: " << m_Path)
    private:
        const char* m_Path;
    };
    
    class CopyFile : public Event
    {
    public:
        CopyFile(const char* copiedFilePath)
            : m_CopiedFilePath(copiedFilePath)
        { }

        EVENT_CLASS_TYPE(CopyFile)
        EVENT_CLASS_CATEGORY(FileSystemCategory)

        EVENT_TO_STRING("CopyFileEvent: " << m_CopiedFilePath)
    private:
        const char* m_CopiedFilePath;
    };

    class DeleteFile : public Event
    {
    public:
        DeleteFile(const char* deleteFilePath)
            : m_DeleteFilePath(deleteFilePath)
        { }

        EVENT_CLASS_TYPE(DeleteFile)
        EVENT_CLASS_CATEGORY(FileSystemCategory)

        EVENT_TO_STRING("DeleteFileEvent: " << m_DeleteFilePath)
    private:
        const char* m_DeleteFilePath;
    };

    class MoveFile : public Event
    {
    public:
        MoveFile(const char* moveFilePath)
            : m_MoveFilePath(moveFilePath)
        { }

        EVENT_CLASS_TYPE(MoveFile)
        EVENT_CLASS_CATEGORY(FileSystemCategory)

        EVENT_TO_STRING("MoveFileEvent: " << m_MoveFilePath)
    private:
        const char* m_MoveFilePath;
    };

    class NewFile : public Event
    {
    public:
        NewFile(const char* newFilePath)
            : m_NewFilePath(newFilePath)
        { }

        EVENT_CLASS_TYPE(NewFile)
        EVENT_CLASS_CATEGORY(FileSystemCategory)

        EVENT_TO_STRING("NewFileEvent: " << m_NewFilePath)
    private:
        const char* m_NewFilePath;
    };
}