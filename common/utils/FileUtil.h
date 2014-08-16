#ifndef UTIL_FILE_UTIL_H
#define UTIL_FILE_UTIL_H

#include <common.h>
#include <sys/types.h>
#include <sys/stat.h>

namespace dyc {

class FileUtil
{
public:
    static bool ReadLocalFile(const std::string &filePath, std::string& content);
    static bool GetRealPath(const std::string &path, std::string &realPath);
    static bool IsDirExist(const std::string& dir);
    static bool IsFileExist(const std::string& file);
    static bool CopyFile(const std::string& src, const std::string& dest);
    static bool CreateDir(const std::string& dir, mode_t mode = S_IRWXU);
    static bool RecursiveDeleteLocalDir(const std::string& dir);
    static bool DeleteLocalFile(const std::string &localFilePath);
    static ssize_t ReadN(int fd, char *buf, size_t n);
    static ssize_t WriteN(int fd, char *buf, size_t n);

private:
    static const char DIR_DELIM = '/';
};

}

#endif //UTIL_FILE_UTIL_H
