#ifndef __HEADER_H__
#define __HEADER_H__

#include <iostream>
#include <libelf.h>
#include <gelf.h>

#include "common.h"

//      typedef struct
//      {
//        unsigned char	e_ident[EI_NIDENT];	/* Magic number and other info */
//        Elf32_Half	e_type;			/* Object file type */
//        Elf32_Half	e_machine;		/* Architecture */
//        Elf32_Word	e_version;		/* Object file version */
//        Elf32_Addr	e_entry;		/* Entry point virtual address */
//        Elf32_Off	e_phoff;		/* Program header table file offset */
//        Elf32_Off	e_shoff;		/* Section header table file offset */
//        Elf32_Word	e_flags;		/* Processor-specific flags */
//        Elf32_Half	e_ehsize;		/* ELF header size in bytes */
//        Elf32_Half	e_phentsize;		/* Program header table entry size */
//        Elf32_Half	e_phnum;		/* Program header table entry count */
//        Elf32_Half	e_shentsize;		/* Section header table entry size */
//        Elf32_Half	e_shnum;		/* Section header table entry count */
//        Elf32_Half	e_shstrndx;		/* Section header string table index */
//      } Elf32_Ehdr;
//      

class Header {
public:
    Header(Elf32_Ehdr* header) {_header = header;}
    uint32_t getType() {return _header->e_type;}
    std::string getTypeStr();

    uint32_t getMachine(){return _header->e_machine;}
    std::string getMachineStr();

    uint32_t getVersion(){return _header->e_version;}

    uint32_t getEntry(){return _header->e_entry;}
    uint32_t getPhoff(){return _header->e_phoff;}
    uint32_t getShoff(){return _header->e_shoff;}

    uint32_t getFlags(){return _header->e_flags;}
    std::string getFlagsStr();

    uint32_t getEhsize(){return _header->e_ehsize;}
    uint32_t getPhentsize(){return _header->e_phentsize;}
    uint32_t getPhnum(){return _header->e_phnum;}	 
    uint32_t getShentsize(){return _header->e_shentsize;}
    uint32_t getShnum(){return _header->e_shnum;}	 
    uint32_t getShstrndx(){return _header->e_shstrndx;} 
    void showInfo();
    void parseMagic();

    int check(int fd);

private:
    Elf32_Ehdr* _header;
};

#endif //__HEADER_H__
