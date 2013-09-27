#include "Header.h"

int Header::check(int fd) {
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

    // TODO
    lseek(fd, 0, SEEK_SET);

    if (is32) {
        Elf32_Ehdr head;
        read(fd, (char*)&head, sizeof(head));
        return memcmp(_header, (char*)&head, sizeof(head));
    }
    Elf64_Ehdr head;
    read(fd, (char*)&head, sizeof(head));
    return memcmp(_header, (char*)&head, sizeof(head));
}

Header(Elf32_Ehdr* header) {
    _header = header;
    _is32 = true;
}

Header(Elf32_Ehdr* header) {
    _header64 = header;
    _is32 = false;
}

std::string Header::getTypeStr() {
    if (_header->e_type == ET_REL)
        return "[rel/obj file]";
    if (_header->e_type == ET_EXEC)
        return "[exec file]";
    if (_header->e_type == ET_DYN)
        return "[dynamic file]";
    return "unknow file type";
}

void Header::parseMagic() {
    unsigned char* bitp = _header->e_ident+4;
    if (*bitp == 1) {
        std::cout << "32 bit  ";
    } else {
        std::cout << "64 bit  ";
    }
    unsigned char* endian = bitp + 1;
    if (*endian == 1) {
        std::cout << "little endian";
    } else if (*endian == 2){
        std::cout << "big endian";
    } else {
        std::cout << "invalid endian";
    }
    std::cout << std::endl;
}

void Header::showInfo() {
    parseMagic();
    std::cout << "type: " << getType() << "  " << getTypeStr() << std::endl 
         << "machine: " << getMachine() << "  " << getMachineStr() << std::endl 
         << "version: " << getVersion() << std::endl 
         << "entry: " << std::hex << "0x" << getEntry() << std::endl 
         << "phoff: " << std::dec << getPhoff() << " (" << std::hex << "0x" << getPhoff() << ")" << std::endl 
         << "shoff: " << std::dec << getShoff() << " (" << std::hex << "0x" << getShoff() << ")" << std::endl 
         << "flags: " << getFlags() << std::endl 
         << "ehsize: " << std::dec << getEhsize() << "   while sizeof(_header):" << sizeof(*_header) << std::endl;
}

std::string Header::getMachineStr() {
    if (_header->e_machine == EM_386)
        return "[0x86]";
    else 
        return "unknow machine type";
}


