#include <FileUtil.h>
#include <sys/mman.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <dirent.h>

namespace dyc {

bool FileUtil::ReadLocalFile(const std::string &filePath, std::string& content)
{
    int fd = open(filePath.c_str(), O_RDONLY);
    if (fd == -1) {
        FATAL("open file:[%s] failed", filePath.c_str());
        return false;
    }

    int offset = lseek(fd, 0, SEEK_END);
    if (offset == -1) {
        FATAL("lseek file:[%s] failed", filePath.c_str());
        return false;
    }
    if (lseek(fd, 0, SEEK_SET) == -1) {
        FATAL("lseek file:[%s] failed", filePath.c_str());
        return false;
    }

    content.reserve(offset);
    const int bufLen = 4096;
    char buf[bufLen];
    bool ret = true;
    ssize_t readLen = 0;
    while ((readLen = read(fd, buf, bufLen))) {
        if (readLen < 0 && errno != EINTR) {
            FATAL("read file [%s] error: %s", filePath.c_str(), strerror(errno));
            ret = false;
            break;
        }
        if (readLen > 0) {
            content.append(buf, readLen);
        }
    }

    close(fd);
    if (!ret) {
        return false;
    }
    return true;;
}

bool FileUtil::GetRealPath(const std::string &path, std::string &realPath)
{
    char resolvedPath[PATH_MAX];
    char *result = realpath(path.c_str(), resolvedPath);
    if (result == NULL) {
        return false;
    }
    realPath.assign(resolvedPath);
    return true;
}


}
