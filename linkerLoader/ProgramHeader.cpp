#include "ProgramHeader.h"

void ProgramHeader::showInfo() {
    std::cout << "type: " << getType() << "  type: " << getTypeStr() << std::endl 
         << "vaddr: " << std::hex << "0x" << getVaddr() << std::endl 
         << "paddr: " << std::hex << "0x" << getPaddr() << std::endl 
         << "filesz: " << std::dec << getFilesz() << std::endl 
         << "memsz: " << std::dec << getMemsz() << std::endl 
         << "flags: " << getFlags() << "  " << getFlagsStr() << std::endl 
         << "align: " << getAlign() << std::endl;
}


std::string ProgramHeader::getFlagsStr() {
    return "";
}

std::string ProgramHeader::getTypeStr() {
    std::string s;
#define C(V) case PT_##V: s = #V; break
        switch (getType()) {
            C(NULL);        C(LOAD);        C(DYNAMIC);
            C(INTERP);      C(NOTE);        C(SHLIB);
            C(PHDR);        C(TLS);         
            C(SUNWBSS);     C(SUNWSTACK);   
            default:
            s = "unknown";
            break;
        }
#undef  C
        return s;
}


