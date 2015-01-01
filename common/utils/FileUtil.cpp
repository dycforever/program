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

#include "utils/FileUtil.h"

namespace dyc {


bool FileUtil::ReadLocalFile(const std::string &filePath, std::string& content)
{
    int fd = open(filePath.c_str(), O_RDONLY);
    if (fd == -1) {
//        FATAL_LOG("open file:[%s] failed", filePath.c_str());
        return false;
    }

    int offset = lseek(fd, 0, SEEK_END);
    if (offset == -1) {
//        FATAL_LOG("lseek file:[%s] failed", filePath.c_str());
        return false;
    }
    if (lseek(fd, 0, SEEK_SET) == -1) {
//        FATAL_LOG("lseek file:[%s] failed", filePath.c_str());
        return false;
    }

    content.reserve(offset);
    const int bufLen = 4096;
    char buf[bufLen];
    bool ret = true;
    ssize_t readLen = 0;
    while ((readLen = read(fd, buf, bufLen))) {
        if (readLen < 0 && errno != EINTR) {
//            FATAL_LOG("read file [%s] error: %s", filePath.c_str(), strerror(errno));
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

bool FileUtil::IsDirExist(const std::string& dirPath)
{
    struct stat st;
    if (stat(dirPath.c_str(), &st) != 0) {
        return false;
    }
    if (!S_ISDIR(st.st_mode)) {
        return false;
    }
    return true;
}

bool FileUtil::IsFileExist(const std::string& filePath)
{
    struct stat st;
    if (stat(filePath.c_str(), &st) != 0) {
        return false;
    }
    if (!S_ISREG(st.st_mode)) {
        return false;
    }
    return true;
}

bool FileUtil::CopyFile(const std::string& srcFile, const std::string& destFile)
{
    int fileIn = open(srcFile.c_str(), O_RDONLY);
    if (fileIn == -1) {
//        FATAL_LOG("open file [%s] failed", srcFile.c_str());
        return false;
    }

    int fileOut = open(destFile.c_str(), O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fileOut == -1) {
//        FATAL_LOG("open file [%s] failed", destFile.c_str());
        close(fileIn);
        return false;
    }

    const int bufLen = 4096;
    char buf[bufLen];

    bool ret = true;
    while (true) {
        ssize_t readLen = ReadN(fileIn, buf, bufLen);
        if (readLen < 0) {
            ret = false;
            break;
        } else if (readLen == 0) {
            break;
        } else {
            ssize_t writeLen = WriteN(fileOut, buf, readLen);
            if (writeLen < readLen) {
                ret = false;
                break;
            }
        }
    }

    close(fileIn);
    close(fileOut);
    return ret;
}

bool FileUtil::CreateDir(const std::string& dir, mode_t mode)
{
    return mkdir(dir.c_str(), mode) == 0;
}

bool FileUtil::RecursiveDeleteLocalDir(const std::string& localDirPath)
{
    DIR *dir = NULL;
    struct dirent *dp = NULL;

    if ((dir = opendir(localDirPath.c_str())) == NULL) {
//        FATAL_LOG("opendir localDirPath [%s] failed", localDirPath.c_str());
        return false;
    }

    bool retFlag = false;
    while((dp = readdir(dir)) != NULL) {
        if (dp->d_type & DT_DIR) {
            if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0) {
                retFlag = true;
                continue;
            } else {
                std::string childDirPath = localDirPath + DIR_DELIM + std::string(dp->d_name);
                retFlag = RecursiveDeleteLocalDir(childDirPath);
            }
        } else {
            std::string childFilePath = localDirPath + DIR_DELIM + std::string(dp->d_name);
            retFlag = DeleteLocalFile(childFilePath);
        }

        if (!retFlag) {
            break;
        }
    }
    closedir(dir);

    //rm itself
    if (retFlag && rmdir(localDirPath.c_str()) != 0) {
//        FATAL_LOG("rmdir localDirPath [%s] failed", localDirPath.c_str());
        return false;
    }

    return retFlag;
}

bool FileUtil::DeleteLocalFile(const std::string &localFilePath)
{
    return (0 == unlink(localFilePath.c_str()));
}

ssize_t FileUtil::ReadN(int fd, char *buf, size_t n)
{
    size_t leftLen = n;
    ssize_t readLen = 0;
    while (leftLen > 0) {
        readLen = read(fd, buf, leftLen);
        if (readLen < 0 && errno != EINTR) {
//            FATAL_LOG("read file failed [%s]", strerror(errno));
            return -1;
        } else if (readLen == 0) {
            break;
        } else if (readLen > 0) {
            buf += readLen;
            leftLen -= readLen;
        }
    }

    return (ssize_t)n - leftLen;
}

ssize_t FileUtil::WriteN(int fd, char *buf, size_t n)
{
    size_t leftLen = n;
    ssize_t writeLen = 0;
    while (leftLen > 0) {
        writeLen = write(fd, buf, leftLen);
        if (writeLen < 0 && errno != EINTR) {
//            FATAL_LOG("write file failed [%s]", strerror(errno));
            return -1;
        } else if (writeLen == 0) {
            break;
        } else if (writeLen > 0) {
            buf += writeLen;
            leftLen -= writeLen;
        }
    }

    return (ssize_t)n - leftLen;
}


}

