/***************************************************************************************
* Copyright (c) 2014-2022 Zihao Yu, Nanjing University
*
* NEMU is licensed under Mulan PSL v2.
* You can use this software according to the terms and conditions of the Mulan PSL v2.
* You may obtain a copy of Mulan PSL v2 at:
*          http://license.coscl.org.cn/MulanPSL2
*
* THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
* EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
* MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
*
* See the Mulan PSL v2 for more details.
***************************************************************************************/

#include <isa.h>

word_t isa_raise_intr(word_t NO, vaddr_t epc) {
  /* TODO: Trigger an interrupt/exception with ``NO''.
   * Then return the address of the interrupt/exception vector.
   */

  #ifdef CONFIG_ETRACE
  printf("\n-------------------------\n");
  printf("ETRACE:NO is %ld\tEPC is %lx\n",NO,epc);  //etrace
  printf("\n-------------------------\n");
  #endif
  cpu.csr.mcause = NO;  
  cpu.csr.mepc = epc; 
  // cpu.csr.mstatus = 0xa00001800;

  word_t old_mstatus = cpu.csr.mstatus;
  cpu.csr.mstatus = ( (BITS(old_mstatus, 36, 13) << 13) | (BITS(3, 1, 0) << 11) | (BITS(old_mstatus, 10, 8) << 8) | (BITS(old_mstatus, 3, 3) << 7) | (BITS(old_mstatus, 6, 4) << 4) | (BITS(0, 1, 1) << 3) | (BITS(old_mstatus, 2, 0)) ) ;
  #ifdef CONFIG_ETRACE
  printf("\n+++++\necall:\told mstatus: %lx, new mstatus:%lx\n", old_mstatus, cpu.csr.mstatus);
  #endif
  return cpu.csr.mtvec; //返回异常地址入口
}

word_t isa_query_intr() {
  return INTR_EMPTY;
}
