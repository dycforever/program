
#include <libelf.h>
#include <gelf.h>
#include <stdio.h>

#include "common.h"
#include "Header.h"

using namespace dyc;
using namespace std;

void dumpMem(string out, char* buf, size_t size) {
    FILE* fpout = fopen(out.c_str(), "w");
    fwrite(buf, 1, size, fpout);
    fclose(fpout);
}

int check(int fd, Elf32_Ehdr* _header) {
    char hh[5];
    bool is32;
    read(fd, hh, 5);
    if (hh[4] == 1) {
        is32= true;
    } else if (hh[4] == 2) {
        is32= false;
    } else {
        return -1;
    }

    if (is32) {
        Elf32_Ehdr head;
        int count = read(fd, (char*)&head, sizeof(head));
        CHECK_ERROR(-1, count == sizeof(head), "read elf_failed ");
        dumpMem("mem.out", (char*)&head, sizeof(head));
        return 0;

        Header* h1 = NEW Header(&head);
        h1->showInfo();
        printf("\n");
        Header* h2 = NEW Header(_header);
        h2->showInfo();

        dumpMem("mem.std", (char*)_header, sizeof(*_header));
        return memcmp(_header, (char*)&head, sizeof(head));
    }
    Elf64_Ehdr head;
    int count = read(fd, (char*)&head, sizeof(head));
    CHECK_ERROR(-1, count == sizeof(head), "read elf_failed ");
    return memcmp(_header, (char*)&head, sizeof(head));
}

int main() {

    elf_version(EV_CURRENT);
    string fileName("a.out");
    int fd = open(fileName.c_str(), O_RDONLY);
    CHECK_ERROR(-1, fd >= 0, "open %s failed", fileName.c_str());

    Elf* _elf = elf_begin(fd, ELF_C_READ, NULL);
    CHECK_ERROR(-1, _elf != NULL, "elf_begin failed %d %s", elf_errno(), elf_errmsg(elf_errno()));

    Elf32_Ehdr* elf_header = elf32_getehdr(_elf);
    CHECK_ERROR(-1, elf_header != NULL, "get elf header failed");

    int fd2 = open(fileName.c_str(), O_RDONLY);
    CHECK_ERROR(-1, fd2 >= 0, "open %s failed", fileName.c_str());

    int ret = check(fd2, elf_header);
    printf("run success %d\n", ret);
}
