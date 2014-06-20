#ifndef FILE_UTIL_H
#define FILE_UTIL_H

#include <common.h>
#include <log.h>

namespace dyc {

class FileUtil
{
public:
    static bool ReadLocalFile(const std::string &filePath, std::string& content);
    static bool GetRealPath(const std::string &path, std::string &realPath);

};

}

#endif //FILE_UTIL_H
