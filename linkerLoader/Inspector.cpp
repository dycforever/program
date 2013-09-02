#include <iostream>
#include <libelf.h>
#include <gelf.h>

#include "common.h"
#include "Header.h"
#include "ProgramHeader.h"
#include "SectionHeader.h"

using namespace dyc;
using namespace std;

void dumpfile(string in, string out, size_t off, size_t size) {
    FILE* fpin = fopen(in.c_str(), "r");
    FILE* fpout = fopen(out.c_str(), "w");
    assert(fpin != NULL && fpout != NULL);
    fseek(fpin, off, SEEK_SET);
    char* buf = NEW char[size];
    fread(buf, 1, size, fpin);
    fwrite(buf, 1, size, fpout);
    DELETES(buf);
    fclose(fpin);
    fclose(fpout);
}

void printGElf_Shdr (GElf_Shdr* shdr) {
    cout << endl << "output gelf info : " << endl;
    cout << "type: " << shdr->sh_type << endl 
    << "flags: " << shdr->sh_flags << endl 
    << "addr: " << hex << "0x" << shdr->sh_addr << endl 
    << "offset: " << hex << "0x" << shdr->sh_offset << endl 
    << "size: " << dec << shdr->sh_size << endl 
    << "link: " << dec << shdr->sh_link << endl 
    << "info: " << dec << shdr->sh_info << endl 
    << "align: " << shdr->sh_addralign << endl
    << "entsize: " << shdr->sh_entsize << endl;
}

void printElf32_Shdr (Elf32_Shdr* shdr) {
    cout << endl << "output elf32 info : " << endl;
    cout << "type: " << shdr->sh_type << endl 
    << "flags: " << shdr->sh_flags << endl 
    << "addr: " << hex << "0x" << shdr->sh_addr << endl 
    << "offset: " << hex << "0x" << shdr->sh_offset << endl 
    << "size: " << dec << shdr->sh_size << endl 
    << "link: " << dec << shdr->sh_link << endl 
    << "info: " << dec << shdr->sh_info << endl 
    << "align: " << shdr->sh_addralign << endl
    << "entsize: " << shdr->sh_entsize << endl;
}

void dumpMem(string out, char* buf, size_t size) {
    FILE* fpout = fopen(out.c_str(), "w");
    fwrite(buf, 1, size, fpout);
    fclose(fpout);
}

class Inspector {
public:
    int inspect (const string& fileName);
    Header* getHeader();

private:
    uint64_t _rawFileSize;
    char* _rawFile;
    Elf* _elf;
    Header* _header;

    vector<ProgramHeader*> phentrys;
    vector<SectionHeader*> shentrys;
};

int Inspector::inspect(const string& fileName) {
    int fd = open(fileName.c_str(), O_RDONLY);
    CHECK_ERROR(-1, fd >= 0, "open %s failed", fileName.c_str());

    elf_version(EV_CURRENT);
    _elf = elf_begin(fd, ELF_C_READ, NULL);
    CHECK_ERROR(-1, _elf != NULL, "elf_begin failed %d %s", elf_errno(), elf_errmsg(elf_errno()));

    Elf32_Ehdr* elf_header = elf32_getehdr(_elf);
    CHECK_ERROR(-1, elf_header != NULL, "get elf header failed");
    _header = NEW Header(elf_header);

    int ret = getFileSize(fileName.c_str(), _rawFileSize);
    CHECK_ERROR(-1, ret == 0, "get file size failed");
    _rawFile = NEW char[_rawFileSize];
    CHECK_ERROR(-1, _rawFile != NULL, "new _rawFile failed, size: %llu", _rawFileSize);
    uint64_t uret = read(fd, _rawFile, _rawFileSize);
    CHECK_ERROR(-1, uret == _rawFileSize, "read _rawFile failed, read: %llu != %llu", uret, _rawFileSize);
    
    for (unsigned int i=0; i<_header->getPhnum(); ++i) {
        GElf_Phdr* phdr = NEW GElf_Phdr();
        gelf_getphdr(_elf, i, phdr);
        ProgramHeader* phentry = NEW ProgramHeader(phdr);
//        cout << "\n\n program head " << i << endl;
//        phentry->showInfo();
        phentrys.push_back(phentry);
    }

    Elf_Scn* scn = NULL; 
    int i = 0;
    while ((scn = elf_nextscn(_elf, scn)) != NULL) {
        ++i;
        GElf_Shdr* shdr = NEW GElf_Shdr;
        if (gelf_getshdr(scn, shdr) != shdr){
            FATAL("get shdr failed");
            break;
        }
        printElf32_Shdr((Elf32_Shdr*)(_rawFile+0x130+40));
        printGElf_Shdr((GElf_Shdr*)shdr);
        dumpMem("mem.out", (char*)shdr, sizeof(*shdr));
        break;
        SectionHeader* shentry = NEW SectionHeader(shdr, _rawFile);
//        cout << "\n\n section head " << i << endl;
//        shentry->showInfo();
        shentrys.push_back(shentry);
    }

    if ((unsigned int)i != _header->getShnum()) {
        WARNING("i %d != shnum %u", i, _header->getShnum());
    }

    return 0;
}

Header* Inspector::getHeader() {
    return _header;
}

int main (int argc, char** argv) {
    Inspector inspector;
    cout << "argc = " << argc << endl;
    string file;
    if (argc < 2) {
        cerr << "usage: ./Inspector filename" << endl;
        file = "a.out";
    }
    else {
         file = argv[1];
    }
    int ret = inspector.inspect(file);
    assert (ret == 0);

    Header* header = inspector.getHeader();
    assert(header != NULL);
    header->showInfo();
    
    NOTICE("run success");
}
