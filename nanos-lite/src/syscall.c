#include <common.h>
#include "syscall.h"
#include <sys/time.h>

void do_syscall(Context *c) {
  uintptr_t a[4];
  a[0] = c->GPR1;   //a7
  a[1] = c->GPR2;   //a0
  a[2] = c->GPR3;   //a1
  a[3] = c->GPR4;
  // printf("\n\n-----\ndo_syscall\ta[0]:%d\ta[1]:%d\ta[2]:%d\ta[3]:%d\tc->gprx:%d\n-----\n\n",a[0],a[1],a[2],a[3],c->GPRx); //strace GPRX:a0

  #ifdef CONFIG_STRACE
        printf("\n-----\nSTRACE: %s: sys_num is %d\n-----\n",SYS_names[a[0]],a[0]);
  #endif

  switch (a[0]) {
    case SYS_exit: halt(a[1]); break;
    case SYS_yield: yield();  c->GPRx = 0;  break;
    default: panic("Unhandled syscall ID = %d", a[0]);
  }

}
