
#include <fstream>
#include <sstream>
#include <sys/sendfile.h>

#include "rawlog.h"

#include "cmd_args.h"

using namespace std;
using namespace dyc;

const int BUFFER_SIZE=10;

int checkPos (FILE* fp, off_t pos, char c) {
    fseek(fp, pos, SEEK_SET);
    char cc;
    fread(&cc, 1, 1, fp);
    if (cc != c) {
        printf("fail in check pos[%ld] char[%c]", pos, cc);
        assert(false);
    }
}


void findchar(FILE* fp, off_t start, vector<off_t>& delimiters) {
    DEBUG_LOG("in find char");
    assert(fseek(fp, start, SEEK_SET) == 0);
    char buf[BUFFER_SIZE];
    bool found = false;
    size_t hasRead = 0;
    do {
        size_t readCount = fread(buf, 1, sizeof(buf), fp);
        if (readCount != sizeof(buf)) {
            if (feof(fp)) {
                DEBUG_LOG("PUSH file over %ld", start + hasRead + readCount);
                delimiters.push_back(start + hasRead + readCount);
            } else {
                FATAL_LOG("read failed:");
                delimiters.push_back(-1);
            }
            break;
        }
        for (int i=0; i<sizeof(buf); ++i) {
            if (buf[i] == '\n') {
                DEBUG_LOG("PUSH CR %ld", start + hasRead + readCount);
                delimiters.push_back(start + hasRead + i);
                checkPos(fp, start + hasRead + i, '\n');
                found = true;
                break;
            }
        }
        hasRead += readCount;
    } while(!found);
}


int main(int argc, char** argv) {
    CmdArgs args;
    if (!args.Parse(argc, argv)) {
        args.PrintHelp();
        return 0;
    }

    const string filename = args.GetInputFile();
    struct stat fileInfo;
    assert(stat(filename.c_str(), &fileInfo) == 0);
    size_t fileSize = fileInfo.st_size;

    size_t partCount = args.GetThreadPoolSize();
    size_t partSize = fileSize/partCount;
    printf("partSize: %lu, partCount: %lu\n", partSize, partCount);
    vector<off_t> delimiters;

    FILE* fp = fopen(filename.c_str(), "r");

    for (int i=1; i<partCount; ++i) {
        findchar(fp, i * partSize, delimiters);
    }

    // confirm
    NOTICE_LOG("size: %ld", delimiters.size());
    assert(fseek(fp, 0, SEEK_SET) == 0);
    for (int i=0; i<delimiters.size(); i++) {
//        std::cout << delimiters[i] << std::endl;
        if (delimiters[i] == -1) {
            FATAL_LOG("something wrong");
        } else if(delimiters[i] != fileSize) {
            checkPos(fp, delimiters[i], '\n');
            NOTICE_LOG("check pass");
        }
    }
    fclose(fp);

    // start points
    std::vector<off_t> startPos;
    startPos.push_back(0);
    for (int i=0; i<delimiters.size(); i++) {
        if (delimiters[i] != fileSize)
            startPos.push_back(delimiters[i] + 1);
        else 
            startPos.push_back(fileSize);
    }

    // output parts
    size_t size = 0;
    int fdin = open(filename.c_str(), O_RDONLY);
    if (fdin < 0) {
        std::cout << "call output: " << fdin << " errno: " << errno << std::endl;
        return -1;
    }
    for (int i=0; i < startPos.size(); i++) {
        std::stringstream ss;
        ss << "part." << i;
        std::string outfile = ss.str();
        off_t offset = startPos[i];
        if (i != startPos.size() - 1)
            size = startPos[i+1] - startPos[i];
        else
            size = fileSize - startPos[i];

        int fdout = open(outfile.c_str(), O_WRONLY|O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP);
        if (fdout < 0) {
            std::cout << "open out: " << fdout << " errno: " << errno << strerror(errno) << std::endl;
            return -1;
        }

//        std::cout << "offset: " << offset << " size: " << size << std::endl;
        int ret = sendfile(fdout, fdin, &offset, size);
        if (ret < 0) {
            std::cout << "sendfile ret: " << ret << " errno: " << errno << strerror(errno) << std::endl;
            return -1;
        }
        close(fdout);
    }
    close(fdin);

    printf("all over\n");
}


/*
   struct stat {
   dev_t         st_dev;       //文件的设备编号
   ino_t         st_ino;       //节点
   mode_t        st_mode;      //文件的类型和存取的权限
   nlink_t       st_nlink;     //连到该文件的硬连接数目，刚建立的文件值为1
   uid_t         st_uid;       //用户ID
   gid_t         st_gid;       //组ID
   dev_t         st_rdev;      //(设备类型)若此文件为设备文件，则为其设备编号
   off_t         st_size;      //文件字节数(文件大小)
   unsigned long st_blksize;   //块大小(文件系统的I/O 缓冲区大小)
   unsigned long st_blocks;    //块数
   time_t        st_atime;     //最后一次访问时间
   time_t        st_mtime;     //最后一次修改时间
   time_t        st_ctime;     //最后一次改变时间(指属性)
   };

*/
