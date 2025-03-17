#include <Windows.h>
#include <iostream>
#include <string>

bool isFile(const std::string& filename) {
    DWORD fileAttr = GetFileAttributesA(filename.c_str());
    return (fileAttr != INVALID_FILE_ATTRIBUTES && !(fileAttr & FILE_ATTRIBUTE_DIRECTORY));
}

void printTime(const LARGE_INTEGER& largeTime) {
    FILETIME fileTime;
    SYSTEMTIME systemTime;

    fileTime.dwLowDateTime = largeTime.LowPart;
    fileTime.dwHighDateTime = largeTime.HighPart;

    if (FileTimeToSystemTime(&fileTime, &systemTime)) {
        std::cout << systemTime.wYear << "-"
                  << systemTime.wMonth << "-"
                  << systemTime.wDay << " "
                  << systemTime.wHour << ":"
                  << systemTime.wMinute << ":"
                  << systemTime.wSecond << std::endl;
    } else {
        std::cerr << "Error while translating time." << std::endl;
    }
}

void getFileAttr(DWORD attr) {
    if(attr & FILE_ATTRIBUTE_SYSTEM){
        std::cout << "- System File" << std::endl;
    }

    if (attr & FILE_ATTRIBUTE_READONLY) {
        std::cout << "- Read-only" << std::endl;
    }

    if (attr & FILE_ATTRIBUTE_HIDDEN) {
        std::cout << "- Hidden" << std::endl;
    }

    if (attr & FILE_ATTRIBUTE_DIRECTORY) {
        std::cout << "- Directory" << std::endl;
    }

    if (attr & FILE_ATTRIBUTE_ARCHIVE) {
        std::cout << "- Archive (file attribute)" << std::endl;
    }

    if (attr & FILE_ATTRIBUTE_TEMPORARY) {
        std::cout << "- Temporary" << std::endl;
    }

    if (attr & FILE_ATTRIBUTE_ENCRYPTED) {
        std::cout << "- Encrypted" << std::endl;
    }

    if (attr & FILE_ATTRIBUTE_INTEGRITY_STREAM) {
        std::cout << "- Integrity stream" << std::endl;
    }

    if (attr & FILE_ATTRIBUTE_NO_SCRUB_DATA) {
        std::cout << "- No scrub data" << std::endl;
    }

    if (attr & FILE_ATTRIBUTE_COMPRESSED) {
        std::cout << "- Compressed" << std::endl;
    }

    if (attr & FILE_ATTRIBUTE_OFFLINE) {
        std::cout << "- Offline" << std::endl;
    }

    if (attr & FILE_ATTRIBUTE_NORMAL) {
        std::cout << "- Normal (default attribute)" << std::endl;
    }

    if (attr & FILE_ATTRIBUTE_TEMPORARY) {
        std::cout << "- Temporary" << std::endl;
    }

    if (attr & FILE_ATTRIBUTE_SPARSE_FILE) {
        std::cout << "- Sparse file" << std::endl;
    }

    if (attr & FILE_ATTRIBUTE_REPARSE_POINT) {
        std::cout << "- Reparse point" << std::endl;
    }

    if (attr == 0) {
        std::cout << "- No special attributes" << std::endl;
    }
}

int main() {
    char filename[200];

    std::cout << "File Path: ";
    std::cin >> filename;

    if (!isFile(filename)) {
        std::cerr << "File " << filename << " does not exist." << std::endl;
        return 1;
    }

    HANDLE file = CreateFile(filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (file == INVALID_HANDLE_VALUE) {
        std::cerr << "Impossible to read file data. Error: " << GetLastError() << std::endl;
        return 1;
    }

    FILE_BASIC_INFO fileInfo;
    if (!GetFileInformationByHandleEx(file, FileBasicInfo, &fileInfo, sizeof(FILE_BASIC_INFO ))) {
        std::cerr << "Error while reading file data. Error: " << GetLastError() << std::endl;
        CloseHandle(file);
        return 1;
    }

    std::cout << "Creation Time: " << std::endl;
    printTime(fileInfo.CreationTime);
    std::cout << "Last Access: " << std::endl;
    printTime(fileInfo.LastAccessTime);
    std::cout << "Last Modified: " << std::endl;
    printTime(fileInfo.LastWriteTime);
    std::cout << "Last attributes changes: " << std::endl;
    printTime(fileInfo.ChangeTime);
    std::cout << "File attributes: " << fileInfo.FileAttributes << std::endl;
    getFileAttr(fileInfo.FileAttributes);

    CloseHandle(file);
    system("pause");
    return 0;
}