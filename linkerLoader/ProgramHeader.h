#ifndef __PROGRAMHEADER_H__
#define __PROGRAMHEADER_H__

#include <iostream>
#include <libelf.h>
#include <gelf.h>


/* Program segment header.  */
//    typedef struct
//    {
//      Elf32_Word	p_type;			/* Segment type */
//      Elf32_Off	p_offset;		/* Segment file offset */
//      Elf32_Addr	p_vaddr;		/* Segment virtual address */
//      Elf32_Addr	p_paddr;		/* Segment physical address */
//      Elf32_Word	p_filesz;		/* Segment size in file */
//      Elf32_Word	p_memsz;		/* Segment size in memory */
//      Elf32_Word	p_flags;		/* Segment flags */
//      Elf32_Word	p_align;		/* Segment alignment */
//    } Elf32_Phdr;

template <class ELF_PHDR>
class ProgramHeader {
public:
    ProgramHeader(ELF_PHDR* phentry):_phentry(phentry){}
    uint64_t getType() { return _phentry->p_type; }
    std::string getTypeStr();
    uint64_t getOffset(){ return _phentry->p_offset; }
    uint64_t getVaddr(){ return _phentry->p_vaddr; }
    uint64_t getPaddr(){ return _phentry->p_paddr; }
    uint64_t getFilesz(){ return _phentry->p_filesz; }
    uint64_t getMemsz(){ return _phentry->p_memsz; }
    uint64_t getFlags(){ return _phentry->p_flags; }
    std::string getFlagsStr();
    uint64_t getAlign(){ return _phentry->p_align; }
    void showInfo();
private:
    ELF_PHDR* _phentry;
};

template <class ELF_PHDR>
void ProgramHeader<ELF_PHDR>::showInfo() {
    std::cout << "type: " << getType() << "  type: " << getTypeStr() << std::endl 
         << "vaddr: " << std::hex << "0x" << getVaddr() << std::endl 
         << "paddr: " << std::hex << "0x" << getPaddr() << std::endl 
         << "filesz: " << std::dec << getFilesz() << std::endl 
         << "memsz: " << std::dec << getMemsz() << std::endl 
         << "flags: " << getFlags() << "  " << getFlagsStr() << std::endl 
         << "align: " << getAlign() << std::endl;
}

template <class ELF_PHDR>
std::string ProgramHeader<ELF_PHDR>::getFlagsStr() {
    return "";
}

template <class ELF_PHDR>
std::string ProgramHeader<ELF_PHDR>::getTypeStr() {
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


#endif //__PROGRAMHEADER_H__
