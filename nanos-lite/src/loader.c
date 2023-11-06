#include <proc.h>
#include <elf.h>

#ifdef __LP64__
# define Elf_Ehdr Elf64_Ehdr
# define Elf_Phdr Elf64_Phdr
#else
# define Elf_Ehdr Elf32_Ehdr
# define Elf_Phdr Elf32_Phdr
#endif

extern size_t ramdisk_read(void *buf, size_t offset, size_t len);
extern size_t ramdisk_write(const void *buf, size_t offset, size_t len);

static uintptr_t loader(PCB *pcb, const char *filename) {
// TODO();

  Elf_Ehdr elf_header;

  ramdisk_read(&elf_header, 0, sizeof(Elf_Ehdr) );

  // int64_t mun = *(uint32_t *)elf_header.e_ident;
  // printf("\n-----\ne_ident%p\n-----\n",mun);
  assert(*(uint32_t *)elf_header.e_ident == 0x464C457F);


  Elf_Phdr p_header[elf_header.e_phnum];

  ramdisk_read(p_header, elf_header.e_phoff, sizeof(Elf_Phdr)*elf_header.e_phnum);

  for(int i = 0; i < elf_header.e_phnum; i++){
    if(p_header[i].p_type == PT_LOAD){
      ramdisk_read((void*)(p_header[i].p_paddr) , p_header[i].p_offset , p_header[i].p_memsz);
      memset((void*)(p_header[i].p_filesz + p_header[i].p_vaddr) , 0 , p_header[i].p_memsz - p_header[i].p_filesz);
    }
  }  

  return elf_header.e_entry;

}

void naive_uload(PCB *pcb, const char *filename) {
  uintptr_t entry = loader(pcb, filename);
  Log("Jump to entry = %p", entry);
  ((void(*)())entry) ();
}

