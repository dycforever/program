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
class ProgramHeader {
public:
    ProgramHeader(GElf_Phdr* phentry):_phentry(phentry){}
    uint32_t getType() { return _phentry->p_type; }
    std::string getTypeStr();
    uint32_t getOffset(){ return _phentry->p_offset; }
    uint32_t getVaddr(){ return _phentry->p_vaddr; }
    uint32_t getPaddr(){ return _phentry->p_paddr; }
    uint32_t getFilesz(){ return _phentry->p_filesz; }
    uint32_t getMemsz(){ return _phentry->p_memsz; }
    uint32_t getFlags(){ return _phentry->p_flags; }
    std::string getFlagsStr();
    uint32_t getAlign(){ return _phentry->p_align; }
    void showInfo();
private:
    GElf_Phdr* _phentry;
};


#endif //__PROGRAMHEADER_H__
