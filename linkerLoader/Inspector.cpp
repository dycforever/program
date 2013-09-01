#include <iostream>
#include <libelf.h>
#include <gelf.h>

#include "common.h"

using namespace dyc;
using namespace std;

void dumpfile(string in, string out, size_t off, size_t size) {
    FILE* fpin = fopen(in.c_str(), "r");
    FILE* fpout = fopen(out.c_str(), "w");
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
    string getTypeStr();

    uint32_t getMachine(){return _header->e_machine;}
    string getMachineStr();

    uint32_t getVersion(){return _header->e_version;}

    uint32_t getEntry(){return _header->e_entry;}
    uint32_t getPhoff(){return _header->e_phoff;}
    uint32_t getShoff(){return _header->e_shoff;}

    uint32_t getFlags(){return _header->e_flags;}
    string getFlagsStr();

    uint32_t getEhsize(){return _header->e_ehsize;}
    uint32_t getPhentsize(){return _header->e_phentsize;}
    uint32_t getPhnum(){return _header->e_phnum;}	 
    uint32_t getShentsize(){return _header->e_shentsize;}
    uint32_t getShnum(){return _header->e_shnum;}	 
    uint32_t getShstrndx(){return _header->e_shstrndx;} 
    void showInfo();
    void parseMagic();

private:
    Elf32_Ehdr* _header;
};

string Header::getTypeStr() {
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
        cout << "32 bit  ";
    } else {
        cout << "64 bit  ";
    }
    unsigned char* endian = bitp + 1;
    if (*endian == 1) {
        cout << "little endian";
    } else if (*endian == 2){
        cout << "big endian";
    } else {
        cout << "invalid endian";
    }
    cout << endl;
}

void Header::showInfo() {
    parseMagic();
    cout << "type: " << getType() << "  " << getTypeStr() << endl 
         << "machine: " << getMachine() << "  " << getMachineStr() << endl 
         << "version: " << getVersion() << endl 
         << "entry: " << hex << "0x" << getEntry() << endl 
         << "phoff: " << dec << getPhoff() << " (" << hex << "0x" << getPhoff() << ")" << endl 
         << "shoff: " << dec << getShoff() << " (" << hex << "0x" << getShoff() << ")" << endl 
         << "flags: " << getFlags() << endl 
         << "ehsize: " << dec << getEhsize() << "   while sizeof(_header):" << sizeof(*_header) << endl;
}

string Header::getMachineStr() {
    if (_header->e_machine == EM_386)
        return "[0x86]";
    else 
        return "unknow machine type";
}



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
    string getTypeStr();
    uint32_t getFlags(){ return _shentry->sh_flags; }
    string getFlagsStr();
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

string SectionHeader::getTypeStr() {
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
string SectionHeader::getFlagsStr() {
    string result="";
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
    cout << "type: " << getType() << "  " << getTypeStr() << endl 
    << "flags: " << getFlags() << "  " << getFlagsStr() << endl 
    << "addr: " << hex << "0x" << getAddr() << endl 
    << "offset: " << hex << "0x" << getOffset() << endl 
    << "size: " << dec << getSize() << endl 
    << "link: " << dec << getLink() << endl 
    << "info: " << dec << getInfo() << endl 
    << "align: " << getAddralign() << endl
    << "entsize: " << getEntsize() << endl;
}


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
    string getTypeStr();
    uint32_t getOffset(){ return _phentry->p_offset; }
    uint32_t getVaddr(){ return _phentry->p_vaddr; }
    uint32_t getPaddr(){ return _phentry->p_paddr; }
    uint32_t getFilesz(){ return _phentry->p_filesz; }
    uint32_t getMemsz(){ return _phentry->p_memsz; }
    uint32_t getFlags(){ return _phentry->p_flags; }
    string getFlagsStr();
    uint32_t getAlign(){ return _phentry->p_align; }
    void showInfo();
private:
    GElf_Phdr* _phentry;
};

void ProgramHeader::showInfo() {
    cout << "type: " << getType() << "  type: " << getTypeStr() << endl 
         << "vaddr: " << hex << "0x" << getVaddr() << endl 
         << "paddr: " << hex << "0x" << getPaddr() << endl 
         << "filesz: " << dec << getFilesz() << endl 
         << "memsz: " << dec << getMemsz() << endl 
         << "flags: " << getFlags() << "  " << getFlagsStr() << endl 
         << "align: " << getAlign() << endl;
}


string ProgramHeader::getFlagsStr() {
    return "";
}

string ProgramHeader::getTypeStr() {
        string s;
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

int main () {
    dumpfile("test", "test.out", 0x130+40, sizeof(Elf32_Shdr));
    NOTICE("sizeof(GElf_Shdr) = %d", sizeof(GElf_Shdr));
    NOTICE("sizeof(Elf32_Shdr) = %d", sizeof(Elf32_Shdr));
    Inspector inspector;
    string file = "./test";
    int ret = inspector.inspect(file);
    assert (ret == 0);

    Header* header = inspector.getHeader();
    assert(header != NULL);
    header->showInfo();
    
    NOTICE("run success");
}
