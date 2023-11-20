#include <common.h>
#include "syscall.h"
#include <sys/time.h>

extern int fs_open(const char *pathname, int flags, int mode);
extern size_t fs_write(int fd, const void *buf, size_t len);
extern int fs_close(int fd);
extern size_t fs_read(int fd, void *buf, size_t len);
extern size_t fs_lseek(int fd, size_t offset, int whence);
extern void naive_uload();

const char* SYS_names[] = {
    "SYS_exit",
    "SYS_yield",
    "SYS_open",
    "SYS_read",
    "SYS_write",
    "SYS_kill",
    "SYS_getpid",
    "SYS_close",
    "SYS_lseek",
    "SYS_brk",
    "SYS_fstat",
    "SYS_time",
    "SYS_signal",
    "SYS_execve",
    "SYS_fork",
    "SYS_link",
    "SYS_unlink",
    "SYS_wait",
    "SYS_times",
    "SYS_gettimeofday"
};

// static uintptr_t sys_write(int fd, const void *buf, size_t len){
//   // Log("\n-----\nfd:%d\tlen:%d\n-----\n",fd,len);
//   assert(fd >= 1);
//   uintptr_t i = 0;
//   if(fd ==1 || fd == 2){
//     for(; len > 0 ; len--){
//       putch(((char*)buf)[i]);
//       i++;
//     }
//     return i;
//   }
//   else
//     return -1;
// }

static int sys_gettimeofday(struct timeval* tv , struct timezone *tz ){
 if(tv != NULL){
    tv->tv_usec = io_read(AM_TIMER_UPTIME).us;    //更新微秒
    return 0;
 }
 else{
    return -1;
 }


}

static void sys_execve(const char * proc){
  naive_uload(NULL,proc);
}

void do_syscall(Context *c) {
  uintptr_t a[4];
  a[0] = c->GPR1;   //a7
  a[1] = c->GPR2;   //a0
  a[2] = c->GPR3;   //a1
  a[3] = c->GPR4;
  // printf("\n\n-----\ndo_syscall\ta[0]:%d\ta[1]:%d\ta[2]:%d\ta[3]:%d\tc->gprx:%d\n-----\n\n",a[0],a[1],a[2],a[3],c->GPRx); //strace GPRX:a0

  // char sys_name[] = {SYS_exit,SYS_yield,SYS_open,SYS_read,SYS_write,SYS_kill,SYS_getpid,SYS_close,
//   SYS_lseek,SYS_brk,SYS_fstat,SYS_time,SYS_signal,SYS_execve,SYS_fork,SYS_link,SYS_unlink,SYS_wait,
//   SYS_times,SYS_gettimeofday};
  // int sys_a0 = a[0];
  #ifdef CONFIG_STRACE
        printf("\n-----\nSTRACE: %s: sys_num is %d\n-----\n",SYS_names[a[0]],a[0]);
  #endif

  switch (a[0]) {
    case SYS_exit: 
      // halt(a[1]); 
      // naive_uload(NULL,"/bin/menu"); 
      naive_uload(NULL,"/bin/nterm"); 
      break;
    case SYS_yield: yield();  c->GPRx = 0;  break;
    case SYS_open:  c->GPRx = fs_open((char *)a[1], a[2], a[3]); break;
    case SYS_read:  c->GPRx = fs_read(a[1],(void *)a[2],a[3]);break;
    case SYS_write: c->GPRx = fs_write(a[1], (void *)a[2], a[3]); break;
    case SYS_close: c->GPRx = fs_close(a[1]); break;
    case SYS_lseek: c->GPRx = fs_lseek(a[1],a[2],a[3]); break;
    case SYS_brk:   c->GPRx = 0; break;
    // case SYS_time:  c->GPRx = 0; break;
    case SYS_execve: sys_execve((char *)a[1]); break;
    case SYS_gettimeofday: c->GPRx = sys_gettimeofday((struct timeval *)a[1],(struct timezone *)a[2]); break;
    default: panic("Unhandled syscall ID = %d", a[0]);
  }

}
