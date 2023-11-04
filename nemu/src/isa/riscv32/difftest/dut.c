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
#include <cpu/difftest.h>
#include "../local-include/reg.h"

extern void regs_name_printf();

#define csr_check(name) if (ref_r->csr.name != cpu.csr.name) {\
	printf("\n------------------------------\n");\
	printf("CSR fail at " #name " \nWrong value: %#lx\tRight value: %#lx\t pc: %#lx\n",cpu.csr.name, ref_r->csr.name, ref_r->pc);\
	printf("--------------------------------\n");\
	return false;\
}

bool isa_difftest_checkregs(CPU_state *ref_r, vaddr_t pc) 
{
	int i;
	//gpr[i] check
	for(i=0;i<32;i++){
			if(ref_r->gpr[i] != cpu.gpr[i] ){
				regs_name_printf(i);
				printf("Wrong reg value:%#lx\tRight reg value:%#lx\tdiff value:%#lx\n",cpu.gpr[i],ref_r->gpr[i],cpu.gpr[i] ^ ref_r->gpr[i]);
				
			return false;
			}
		}
	
	//pc check
	if(ref_r->pc != cpu.pc) {
		printf("\nWrong pc %#lx,Right pc %#lx\n",cpu.pc,ref_r->pc);
		return false;
	}


	return true;
}

void isa_difftest_attach() {
}