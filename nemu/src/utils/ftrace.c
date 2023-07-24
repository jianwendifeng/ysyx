#include <common.h>
#include <unistd.h>
#include <elf.h>
#include <stdio.h>



#define func_num_max 64

extern uint64_t g_nr_guest_inst;


//Elf64_Ehdr elf_header;
Elf64_Shdr strtab_hdr, symtab_hdr;
Elf64_Shdr sectionHeader;

Elf64_Sym  func[func_num_max];
int func_num = 0;
Elf64_Addr symbol_start ;
Elf64_Addr symbol_end ;

// 读取字符串表和符号表的内容

void read_symbol_table(FILE *file, Elf64_Shdr symtab_hdr){
    Elf64_Sym* symtab = (Elf64_Sym*)malloc(symtab_hdr.sh_size);
    fseek(file, symtab_hdr.sh_offset, SEEK_SET) ;
    if(fread(symtab, symtab_hdr.sh_size, 1, file) != 1) assert(0);
    int num_syms = symtab_hdr.sh_size / sizeof(Elf64_Sym);
    for (int i = 0; i < num_syms; i++) {
        Elf64_Sym* sym = &symtab[i];
        if (ELF64_ST_TYPE(sym->st_info) == STT_FUNC) {
            func[func_num++] = *sym;
        } 
    }
    free(symtab);
}

void read_string_table(FILE *file, Elf64_Shdr strtab_hdr){
    

}




void init_ftrace(const char *elf_file) {
    FILE *file = fopen(elf_file,"rb");
    if(!file){
        printf("Can't open elf_file.\n");
        fclose(file);
        assert(0);
    }

    Elf64_Ehdr elf_header;
    if(fread(&elf_header, sizeof(Elf64_Ehdr), 1, file) != 1 ) assert(0);
    //assert(fread(&elf_header, sizeof(Elf64_Ehdr), 1, file));

    fseek(file, elf_header.e_shoff, SEEK_SET);
    for (int i = 0; i < elf_header.e_shnum; i++) {
        Elf64_Shdr section_hdr;
        if(fread(&section_hdr, sizeof(Elf64_Shdr), 1, file) !=1 ) assert(0);
        //assert(fread(&section_hdr, sizeof(Elf64_Shdr), 1, file));

        if (section_hdr.sh_type == SHT_STRTAB ) {
            strtab_hdr = section_hdr;
            //assert(strtab_hdr);
        }
        else if (section_hdr.sh_type == SHT_SYMTAB) {
            symtab_hdr = section_hdr;
            //assert(symtab_hdr);
        }
    }
    // 读取字符串表和符号表的内容
    //read_string_table(file, strtab_hdr);
    read_symbol_table(file, symtab_hdr);
    fclose(file);
}

char* get_string_from_offset(Elf64_Xword offset) {
    return (char*)(strtab_hdr.sh_offset + offset);
}


char* find_name(vaddr_t dnpc){
    
    for (int i = 0; i < func_num; i++) {
        Elf64_Addr func_start = func[i].st_value;
        Elf64_Addr func_end = func_start + func[i].st_size;
        if ((dnpc >= func_start) && (dnpc <= func_end)) {
            return  get_string_from_offset(func[i].st_name);
        }
    }
    return "????";
}

static int ftrace_num = 0; 

extern void ftrace_call(vaddr_t pc,vaddr_t dnpc){
    if(func[0].st_info == 0) assert(0) ;
    for(int i = 0 ; i < ftrace_num ; i++){
        printf("0x%#lx: ",pc); 
    char *func_name;
    func_name = find_name(dnpc);
    printf(" call [%s@0x%#lx]",func_name,dnpc);
    ftrace_num++;
}
}

extern void ftrace_ret(vaddr_t pc,vaddr_t dnpc){
    if(func[0].st_value == 0) assert(0);
    for(int i = 0 ; i <= ftrace_num ; i++){
        printf("0x%#lx: ",pc);
    }
    char* func_name = find_name(dnpc);
    printf(" ret [%s@0x%#lx]",func_name,dnpc);
    ftrace_num--;
}






