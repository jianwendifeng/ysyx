#include <common.h>
#include <unistd.h>
#include <elf.h>
#include <stdio.h>



#define func_num_max 64

extern uint64_t g_nr_guest_inst;


Elf64_Ehdr elf_header;
Elf64_Shdr sectionHeader;
Elf64_Shdr sym_tab;     //符号表
Elf64_Shdr str_tab;     //字符串表
Elf64_Sym  func[func_num_max];
int func_num = 0;
Elf64_Addr symbol_start ;
Elf64_Addr symbol_end ;



void init_ftrace(const char *elf_file) {
    FILE *file = fopen(elf_file,"rb");
    if(!file){
        printf("Can't open elf_file.\n");
        fclose(file);
        assert(0);
    }

    // 读取 ELF 文件头
    if(fread(&elf_header, sizeof(Elf64_Ehdr), 1, file) != 1){
        printf("Error reading ELF header\n");
        fclose(file);
        assert(0);
    }

    //int sym_tab_num = sym_tab.sh_size / sizeof(Elf64_Sym);          //符号表的数量
    Elf64_Half sym_tab_num = elf_header.e_shnum;

    int i;
    // 定位节头表
    fseek(file, elf_header.e_shoff, SEEK_SET);
    for (i = 0; i < elf_header.e_shnum; i++) {                          //e_shnum 此成员保存节标题表中的条目数
        if (fread(&sectionHeader, sizeof(Elf64_Shdr), 1, file) != 1) {  //成功读取，文件指针自动移动到下一个要读取的位置
            printf("Error reading section header");
            fclose(file);
            assert(0);
        }
        // 遍历符号表中的每个符号表项

        for (int j = 0; j < sym_tab_num; j++) {
            FILE* psym = file;
            Elf64_Sym symbol;
            if (fread(&symbol, sizeof(Elf64_Sym), 1, psym) != 1) {
                printf("Error reading symbol entry");
                fclose(file);
                assert(0);
            }

            // 判断符号类型是否为 FUNC，如果是则将该符号保存到 func 数组中
            if (ELF64_ST_TYPE(symbol.st_info) == STT_FUNC) {
                if (func_num < func_num_max) {
                    func[func_num++] = symbol;
                } 
                // else {
                //     // 可以选择在 func 数组已满时进行相应的处理，例如跳出循环或者增加数组大小。
                //     // break;
                // }
            }
        }
        if(sectionHeader.sh_type == SHT_STRTAB){
        str_tab = sectionHeader;                    //字符串表节头
        break;
        }
    }
    //unsigned char symbol_type ;  //符号表的类型
    // for(i = 0 ; i < sym_tab_num ; i++ ){
        // if(ELF64_ST_TYPE(sym_tab[i].st_info) == STT_FUNC){
        //    func[func_num++] = sym_tab[i];
        // }
    // }
  fclose(file);
}



char* find_name(vaddr_t dnpc){
    
    for (int i = 0; i < func_num; i++) {
        Elf64_Addr func_start = func[i].st_value;
        Elf64_Addr func_end = func_start + func[i].st_size;
        if ((dnpc >= func_start) && (dnpc <= func_end)) {
            int symbol_name_index = func[i].st_name;
            char* symbol_name = (char*)(str_tab.sh_offset + symbol_name_index);
            return symbol_name;
        }
    }
    return "????";
}

static int ftrace_num = 0; 

void ftrace_call(vaddr_t pc,vaddr_t dnpc){
    if(func[0].st_name == 0) return ;
    for(int i = 0 ; i < ftrace_num ; i++){
        printf("0x%#lx: ",pc); 
    char *func_name;
    func_name = find_name(dnpc);
    printf(" call [%s@0x%#lx]",func_name,dnpc);
    ftrace_num++;
}
}

void ftrace_ret(vaddr_t pc,vaddr_t dnpc){
    if(func[0].st_name == 0) return ;
    for(int i = 0 ; i <= ftrace_num ; i++){
        printf("0x%#lx: ",pc);
    }
    char* func_name = find_name(dnpc);
    printf(" ret [%s@0x%#lx]",func_name,dnpc);
    ftrace_num--;
}






