#include <fs.h>

extern size_t ramdisk_read(void *buf, size_t offset, size_t len);
extern size_t ramdisk_write(const void *buf, size_t offset, size_t len);
extern size_t events_read(void *buf, size_t offset, size_t len);
extern size_t serial_write(const void *buf, size_t offset, size_t len);
extern size_t fb_write(const void *buf, size_t offset, size_t len);
extern size_t dispinfo_read(void *buf, size_t offset, size_t len) ;


typedef size_t (*ReadFn) (void *buf, size_t offset, size_t len);
typedef size_t (*WriteFn) (const void *buf, size_t offset, size_t len);

typedef struct {
  char *name;
  size_t size;
  size_t disk_offset;
  ReadFn read;
  WriteFn write;
} Finfo;

enum {FD_STDIN, FD_STDOUT, FD_STDERR,  FD_EVENT, FD_DISPINFO,FD_FB};
size_t open_offset = 0;   //偏移量

size_t invalid_read(void *buf, size_t offset, size_t len) {
  panic("should not reach here");
  return 0;
}

size_t invalid_write(const void *buf, size_t offset, size_t len) {
  panic("should not reach here");
  return 0;
}

/* This is the information about all files in disk. */
static Finfo file_table[] __attribute__((used)) = {
  [FD_STDIN]  = {"stdin", 0, 0, invalid_read, invalid_write},
  [FD_STDOUT] = {"stdout", 0, 0, invalid_read, serial_write },
  [FD_STDERR] = {"stderr", 0, 0, invalid_read, serial_write },
  [FD_EVENT]  = {"/dev/events", 0, 0, events_read, invalid_write},
  [FD_DISPINFO] = {"/proc/dispinfo", 0, 0, dispinfo_read, invalid_write},
  [FD_FB]     = {"/dev/fb", 0, 0, invalid_read, fb_write},
#include "files.h"
};

int fs_open(const char *pathname, int flags, int mode){
  int fd = -1; //失败返回-1
  
  for(int i = 0 ; i < LENGTH(file_table) ; i++ ) {
  #ifdef CONFIG_STRACE
  printf("\n-----\nNO:%d\tname:%s\tpathname:%s\tlenth:%d\topne_offset:%d\n-----\n",i,file_table[i].name, pathname, LENGTH(file_table),open_offset);
  #endif
    if(strcmp(file_table[i].name, pathname) == 0) {
        fd = i;
        open_offset = 0;
        return fd;
    }
  }
  printf("\n-----\nCan't open file %s\n-----\n",pathname);
  assert(0);
  return -1;
}

size_t fs_read(int fd, void *buf, size_t len) {
  assert(fd > 0);
  Finfo *fp = &file_table[fd];
  size_t file_size = fp->size;
  size_t disk_offset = fp->disk_offset;

  if(fp->read != NULL){
    return fp->read(buf,0,len);
  }
  else {
    // printf("\n-----\nNo.1\topen_offset%p\tlen:%p\tdisk_offset:%p\n------\n",open_offset,len,file_size);
    if(open_offset > file_size){
     assert(0);
    }
    if ((open_offset + len) > file_size) {  
      len = file_size - open_offset;
    }
    // printf("\n-----\nNo.2\topen_offset%p\tdisk_offset:%p\tlen:%p\tfile_size:%p\n------\n",open_offset,disk_offset,file_size);
    ramdisk_read(buf, disk_offset + open_offset, len);
    open_offset += len;
    return len;
  }
}


size_t fs_write(int fd, const void *buf, size_t len){
  if(len == 0){
    printf("\n-----\nlen  is 0.\n-----\n");
  }

  size_t ret = -1;

  Finfo *fp = &file_table[fd];
  if(fp->write != NULL) {
    ret = fp->write(buf, 0, len); //按照讲义，offset不考虑
    return ret;   //返回写入的字节数量
  }
  else {
    size_t ramdisk_offset = fp->disk_offset + open_offset;
    ret = ramdisk_write(buf, ramdisk_offset, len);
    open_offset += ret;
    return ret;   //返回写入的长度
  }
  return ret;    //错误时返回-1
}


size_t fs_lseek(int fd, size_t offset, int whence){
  Finfo *fp = &file_table[fd];
  if(offset > file_table[fd].size) assert(0);
  #ifdef CONFIG_STRACE
  printf("\n-----\nwhence:%d\n-----\n",whence);
  #endif
  switch (whence)
  {
  case SEEK_SET:
    open_offset = offset;
    break;
  case SEEK_CUR:
    open_offset += offset;
    break;
  case SEEK_END:
    open_offset = fp->size + offset;
    break;
   default:
      panic("\n-----\nfs_lseek whence haven't set.\n-----\n");
      return -1;
      break;
  }
  #ifdef CONFIG_STRACE
  printf("offset is %d\n", open_offset);
  #endif
  return open_offset;
}


int fs_close(int fd) {
  open_offset = 0;
  return 0;
}

void init_fs() {
  // TODO: initialize the size of /dev/fb
  AM_GPU_CONFIG_T gpu = io_read(AM_GPU_CONFIG);
  // printf("\n-----\ngpu.width:%d\tgpu.height:%d\n-----\n",gpu.width,gpu.height);
  file_table[FD_FB].size = gpu.width * gpu.height; 
}
