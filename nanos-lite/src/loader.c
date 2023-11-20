#include <proc.h>
#include <elf.h>
#include <fs.h>

#ifdef __LP64__
# define Elf_Ehdr Elf64_Ehdr
# define Elf_Phdr Elf64_Phdr
#else
# define Elf_Ehdr Elf32_Ehdr
# define Elf_Phdr Elf32_Phdr
#endif


#if defined(__ISA_AM_NATIVE__)
# define EXPECT_TYPE EM_X86_64
#elif defined(__ISA_X86__)
# define EXPECT_TYPE EM_X86_64
#elif defined(__ISA_MIPS32__)
# define EXPECT_TYPE EM_MIPS
#elif defined(__ISA_RISCV32__) || defined(__ISA_RISCV64__)
# define EXPECT_TYPE EM_RISCV
#else 
#error Unsupported ISA
#endif

extern size_t ramdisk_read(void *buf, size_t offset, size_t len);
extern size_t ramdisk_write(const void *buf, size_t offset, size_t len);
extern int fs_open(const char *pathname, int flags, int mode);
extern size_t fs_read(int fd, void *buf, size_t len);
extern size_t fs_write(int fd, const void *buf, size_t len);
extern size_t fs_lseek(int fd, size_t offset, int whence);
extern int fs_close(int fd);

// static uintptr_t loader(PCB *pcb, const char *filename) {
// // TODO();

//   Elf_Ehdr elf_header;

//   ramdisk_read(&elf_header, 0, sizeof(Elf_Ehdr) );

//   // int64_t mun = *(uint32_t *)elf_header.e_ident;
//   // printf("\n-----\ne_ident%p\n-----\n",mun);
//   assert(*(uint32_t *)elf_header.e_ident == 0x464C457F);

//   Elf_Phdr p_header[elf_header.e_phnum];

//   ramdisk_read(p_header, elf_header.e_phoff, sizeof(Elf_Phdr)*elf_header.e_phnum);

//   for(int i = 0; i < elf_header.e_phnum; i++){
//     if(p_header[i].p_type == PT_LOAD){
//       ramdisk_read((void*)(p_header[i].p_paddr) , p_header[i].p_offset , p_header[i].p_memsz);
//       memset((void*)(p_header[i].p_filesz + p_header[i].p_vaddr) , 0 , p_header[i].p_memsz - p_header[i].p_filesz);
//     }
//   }  
//   return elf_header.e_entry;
// }

static uintptr_t loader(PCB *pcb, const char *filename) {
//   // TODO();

//   Elf_Ehdr elf_header;
  int fd = fs_open(filename, 0, 0);
  assert(fd >= 0);
  Elf_Ehdr Ehdr;
//   ramdisk_read(&elf_header, 0, sizeof(Elf_Ehdr) );

//   // int64_t mun = *(uint32_t *)elf_header.e_ident;
//   // printf("\n-----\ne_ident%p\n-----\n",mun);
//   assert(*(uint32_t *)elf_header.e_ident == 0x464C457F);

  fs_read(fd, &Ehdr, sizeof(Ehdr));
  
  // printf("\n-----\ne_ident:%d\n-----\n",*(uint32_t*)Ehdr.e_ident);
  assert(*(uint32_t*)Ehdr.e_ident == 0x464c457F);
  assert(Ehdr.e_machine == EXPECT_TYPE);
//   Elf_Phdr p_header[elf_header.e_phnum];
  Elf_Phdr Phdr[Ehdr.e_phnum];
//   ramdisk_read(p_header, elf_header.e_phoff, sizeof(Elf_Phdr)*elf_header.e_phnum);
  fs_lseek(fd, Ehdr.e_phoff, SEEK_SET);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     
  fs_read(fd, Phdr, sizeof(Elf_Phdr)*Ehdr.e_phnum) ;   //
//   for(int i = 0; i < elf_header.e_phnum; i++){
//     if(p_header[i].p_type == PT_LOAD){
//       ramdisk_read((void*)(p_header[i].p_paddr) , p_header[i].p_offset , p_header[i].p_memsz);
//       memset((void*)(p_header[i].p_filesz + p_header[i].p_vaddr) , 0 , p_header[i].p_memsz - p_header[i].p_filesz);
//     }
//   }  
  for(int i = 0 ; i < Ehdr.e_phnum ; i++) {
    if(Phdr[i].p_type == PT_LOAD) {
      fs_lseek(fd, Phdr[i].p_offset, SEEK_SET);
      Elf64_Addr  p_vaddr  = Phdr[i].p_vaddr;
      Elf64_Xword p_memsz  = Phdr[i].p_memsz;
      Elf64_Xword p_filesz = Phdr[i].p_filesz;
      fs_read(fd, (void*)(p_vaddr), p_memsz);
      memset((void*)(p_filesz + p_vaddr) , 0 , p_memsz - p_filesz);
    }
  }
  fs_close(fd);
//   return elf_header.e_entry;
  return Ehdr.e_entry;
}

void naive_uload(PCB *pcb, const char *filename) {
  uintptr_t entry = loader(pcb, filename);
  Log("Jump to entry = %p", entry);
  ((void(*)())entry) ();
}

