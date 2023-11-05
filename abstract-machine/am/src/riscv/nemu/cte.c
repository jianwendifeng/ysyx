#include <am.h>
#include <riscv/riscv.h>
#include <klib.h>

static Context* (*user_handler)(Event, Context*) = NULL;

Context* __am_irq_handle(Context *c) {
#ifdef CONFIG_ETRACE
  printf("\n-----\nc->mcause:%x,\tc->gpr1:%x\n-----\n",c->mcause,c->GPR1);
#endif
  if (user_handler) {
    Event ev = {0};
    switch (c->mcause) {
      case 0xb: //M-mode
        if(c->GPR1 == -1){
          #ifdef CONFIG_ETRACE
          printf("\n-----\n_am_irq_handle\tevent_yeild\n-----\n");
          #endif
          ev.event = EVENT_YIELD; 
          c->mepc = c->mepc + 4;
          break;
        } 
        else if(c->GPR1  >= 0  && c->GPR1 <= 19){
          ev.event = EVENT_SYSCALL;
          c->mepc = c->mepc + 4;
          break;
        }
        
      default: 
        #ifdef CONFIG_ETRACE
        printf("\n-----\nError event\tmcause :%d\n-----\n",c->mcause);
        #endif
        ev.event = EVENT_ERROR; 
        
        break;
    }
    c = user_handler(ev, c);
    assert(c != NULL);
  }

  return c;
}

extern void __am_asm_trap(void);

bool cte_init(Context*(*handler)(Event, Context*)) {
  // initialize exception entry
  asm volatile("csrw mtvec, %0" : : "r"(__am_asm_trap));

  // register event handler
  user_handler = handler;

  return true;
}

Context *kcontext(Area kstack, void (*entry)(void *), void *arg) {
  return NULL;
}

void yield() {
#ifdef __riscv_e
  asm volatile("li a5, -1; ecall");
#else
  asm volatile("li a7, -1; ecall");
#endif
}

bool ienabled() {
  return false;
}

void iset(bool enable) {
}
