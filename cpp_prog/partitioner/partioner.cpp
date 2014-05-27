
#include "common.h"

#include <service_args.h>
#include <fstream>

using namespace std;
using namespace dyc;

const int BUFFER_SIZE=10;

int checkPos (FILE* fp, off_t pos, char c) {
    fseek(fp, pos, SEEK_SET);
    char cc;
    fread(&cc, 1, 1, fp);
    CHECK(cc == c, "fail in check pos[%ld] char[%c]", pos, cc);
}


void findchar(FILE* fp, off_t start, vector<off_t>& delimiters) {
    DEBUG("in find char");
    assert(fseek(fp, start, SEEK_SET) == 0);
    char buf[BUFFER_SIZE];
    bool found = false;
    size_t hasRead = 0;
    do {
        size_t readCount = fread(buf, 1, sizeof(buf), fp);
        if (readCount != sizeof(buf)) {
            if (feof(fp)) {
                DEBUG("PUSH file over %ld", start + hasRead + readCount);
                delimiters.push_back(start + hasRead + readCount);
            } else {
                FATAL_ERROR("read failed:");
                delimiters.push_back(-1);
            }
            break;
        }
        for (int i=0; i<sizeof(buf); ++i) {
            if (buf[i] == '\n') {
                DEBUG("PUSH CR %ld", start + hasRead + readCount);
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
    ServiceArgs args;
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

    for (int i=0; i<partCount; ++i) {
        findchar(fp, (i)*partSize, delimiters);
    }

    NOTICE("size: %ld", delimiters.size());
    assert(fseek(fp, 0, SEEK_SET) == 0);
    for (int i=0; i<delimiters.size(); i++) {
        if (delimiters[i] == -1) {
            FATAL("something wrong");
        } else if(delimiters[i] != fileSize) {
            checkPos(fp, delimiters[i], '\n');
            NOTICE("check pass");
        }
    }
    fclose(fp);
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
