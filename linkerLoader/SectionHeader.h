#ifndef __SECTIONHEADER_H__
#define __SECTIONHEADER_H__

#include <iostream>
#include <libelf.h>
#include <gelf.h>


/* Section header.  */
//  typedef struct
//  {
//    Elf32_Word	sh_name;		/* Section name (string tbl index) */
//    Elf32_Word	sh_type;		/* Section type */
//    Elf32_Word	sh_flags;		/* Section flags */
//    Elf32_Addr	sh_addr;		/* Section virtual addr at execution */
//    Elf32_Off	sh_offset;		/* Section file offset */
//    Elf32_Word	sh_size;		/* Section size in bytes */
//    Elf32_Word	sh_link;		/* Link to another section */
//    Elf32_Word	sh_info;		/* Additional section information */
//    Elf32_Word	sh_addralign;		/* Section alignment */
//    Elf32_Word	sh_entsize;		/* Entry size if section holds table */
//  } Elf32_Shdr;
class SectionHeader {
public:
    SectionHeader(GElf_Shdr* shentry, char* strtbl):_shentry(shentry), _strtbl(strtbl){}
    uint32_t getName();
    uint32_t getType() { return _shentry->sh_type; }
    std::string getTypeStr();
    uint32_t getFlags(){ return _shentry->sh_flags; }
    std::string getFlagsStr();
    uint32_t getAddr(){ return _shentry->sh_addr; }
    uint32_t getOffset(){ return _shentry->sh_offset; }
    uint32_t getSize(){ return _shentry->sh_size; }
    uint32_t getLink(){ return _shentry->sh_link; }
    uint32_t getInfo(){ return _shentry->sh_info; }
    uint32_t getAddralign(){ return _shentry->sh_addralign; }
    uint32_t getEntsize(){ return _shentry->sh_entsize; }
    void showInfo();
private:
    GElf_Shdr* _shentry;
    char* _strtbl;
};

#endif //__SECTIONHEADER_H__
