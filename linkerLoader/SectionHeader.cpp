#include "SectionHeader.h"

//      /* Legal values for sh_type (section type).  */
//      #define SHT_NULL	  0		/* Section header table entry unused */
//      #define SHT_PROGBITS	  1		/* Program data */
//      #define SHT_SYMTAB	  2		/* Symbol table */
//      #define SHT_STRTAB	  3		/* String table */
//      #define SHT_RELA	  4		/* Relocation entries with addends */
//      #define SHT_HASH	  5		/* Symbol hash table */
//      #define SHT_DYNAMIC	  6		/* Dynamic linking information */
//      #define SHT_NOTE	  7		/* Notes */
//      #define SHT_NOBITS	  8		/* Program space with no data (bss) */
//      #define SHT_REL		  9		/* Relocation entries, no addends */
//      #define SHT_SHLIB	  10		/* Reserved */
//      #define SHT_DYNSYM	  11		/* Dynamic linker symbol table */
//      #define SHT_INIT_ARRAY	  14		/* Array of constructors */
//      #define SHT_FINI_ARRAY	  15		/* Array of destructors */
//      #define SHT_PREINIT_ARRAY 16		/* Array of pre-constructors */
//      #define SHT_GROUP	  17		/* Section group */
//      #define SHT_SYMTAB_SHNDX  18		/* Extended section indeces */
//      #define	SHT_NUM		  19		/* Number of defined types.  */
//      #define SHT_LOOS	  0x60000000	/* Start OS-specific.  */
//      #define SHT_GNU_ATTRIBUTES 0x6ffffff5	/* Object attributes.  */
//      #define SHT_GNU_HASH	  0x6ffffff6	/* GNU-style hash table.  */
//      #define SHT_GNU_LIBLIST	  0x6ffffff7	/* Prelink library list */
//      #define SHT_CHECKSUM	  0x6ffffff8	/* Checksum for DSO content.  */
//      #define SHT_LOSUNW	  0x6ffffffa	/* Sun-specific low bound.  */
//      #define SHT_SUNW_move	  0x6ffffffa
//      #define SHT_SUNW_COMDAT   0x6ffffffb
//      #define SHT_SUNW_syminfo  0x6ffffffc
//      #define SHT_GNU_verdef	  0x6ffffffd	/* Version definition section.  */
//      #define SHT_GNU_verneed	  0x6ffffffe	/* Version needs section.  */
//      #define SHT_GNU_versym	  0x6fffffff	/* Version symbol table.  */
//      #define SHT_HISUNW	  0x6fffffff	/* Sun-specific high bound.  */
//      #define SHT_HIOS	  0x6fffffff	/* End OS-specific type */
//      #define SHT_LOPROC	  0x70000000	/* Start of processor-specific */
//      #define SHT_HIPROC	  0x7fffffff	/* End of processor-specific */
//      #define SHT_LOUSER	  0x80000000	/* Start of application-specific */
//      #define SHT_HIUSER	  0x8fffffff	/* End of application-specific */

std::string SectionHeader::getTypeStr() {
    uint32_t type = getType();
    if (type == 1) 
        return "SHT_PROGBITS";
    if (type == 2) 
        return "SHT_SYMTAB";
    if (type == 3) 
        return "SHT_STRTAB";
    if (type == 4) 
        return "SHT_RELA";
    if (type == 5) 
        return "SHT_HASH";
    if (type == 6) 
        return "SHT_DYNAMIC";
    if (type == 7) 
        return "SHT_NOTE";
    if (type == 8) 
        return "SHT_NOBITS";
    if (type == 9) 
        return "SHT_REL";
    if (type == 10) 
        return "SHT_SHLIB";
    return "unknow ";
}

//      /* Legal values for sh_flags (section flags).  */
//      #define SHF_WRITE	     (1 << 0)	/* Writable */
//      #define SHF_ALLOC	     (1 << 1)	/* Occupies memory during execution */
//      #define SHF_EXECINSTR	     (1 << 2)	/* Executable */
//      #define SHF_MERGE	     (1 << 4)	/* Might be merged */
//      #define SHF_STRINGS	     (1 << 5)	/* Contains nul-terminated strings */
//      #define SHF_INFO_LINK	     (1 << 6)	/* `sh_info' contains SHT index */
//      #define SHF_LINK_ORDER	     (1 << 7)	/* Preserve order after combining */
//      #define SHF_OS_NONCONFORMING (1 << 8)	/* Non-standard OS specific handling
//      					   required */
//      #define SHF_GROUP	     (1 << 9)	/* Section is member of a group.  */
//      #define SHF_TLS		     (1 << 10)	/* Section hold thread-local data.  */
//      #define SHF_MASKOS	     0x0ff00000	/* OS-specific.  */
//      #define SHF_MASKPROC	     0xf0000000	/* Processor-specific */
//      #define SHF_ORDERED	     (1 << 30)	/* Special ordering requirement
//      					   (Solaris).  */
//      #define SHF_EXCLUDE	     (1 << 31)	/* Section is excluded unless
//      					   referenced or allocated (Solaris).*/
//      
std::string SectionHeader::getFlagsStr() {
    std::string result="";
    uint32_t flags = getFlags();
    if (flags & SHF_WRITE) {
        result += "SHF_WRITE ";
    }
    if (flags & SHF_ALLOC) {
        result += "SHF_ALLOC ";
    }
    if (flags & SHF_EXECINSTR) {
        result += "SHF_EXECINSTR ";
    }
    if (flags & SHF_MERGE) {
        result += "SHF_MERGE ";
    }
    return result;
}


//uint32_t SectionHeader::getName() {
//    char* start = "";
//    start = ;
//    string name(start);
//}

void SectionHeader::showInfo() {
    std::cout << "type: " << getType() << "  " << getTypeStr() << std::endl 
    << "flags: " << getFlags() << "  " << getFlagsStr() << std::endl 
    << "addr: " << std::hex << "0x" << getAddr() << std::endl 
    << "offset: " << std::hex << "0x" << getOffset() << std::endl 
    << "size: " << std::dec << getSize() << std::endl 
    << "link: " << std::dec << getLink() << std::endl 
    << "info: " << std::dec << getInfo() << std::endl 
    << "align: " << getAddralign() << std::endl
    << "entsize: " << getEntsize() << std::endl;
}


