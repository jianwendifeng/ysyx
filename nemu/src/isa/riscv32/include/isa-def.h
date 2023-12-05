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

<<<<<<< HEAD
#ifndef __ISA_RISCV32_H__
#define __ISA_RISCV32_H__
=======
#ifndef __ISA_RISCV_H__
#define __ISA_RISCV_H__
>>>>>>> 1eba5dd7 (NJU-ProjectN/nemu ics2023 initialized)

#include <common.h>

typedef struct {
<<<<<<< HEAD
  word_t gpr[32];
  vaddr_t pc;
} riscv32_CPU_state;
=======
  word_t gpr[MUXDEF(CONFIG_RVE, 16, 32)];
  vaddr_t pc;
} MUXDEF(CONFIG_RV64, riscv64_CPU_state, riscv32_CPU_state);
>>>>>>> 1eba5dd7 (NJU-ProjectN/nemu ics2023 initialized)

// decode
typedef struct {
  union {
    uint32_t val;
  } inst;
<<<<<<< HEAD
} riscv32_ISADecodeInfo;
=======
} MUXDEF(CONFIG_RV64, riscv64_ISADecodeInfo, riscv32_ISADecodeInfo);
>>>>>>> 1eba5dd7 (NJU-ProjectN/nemu ics2023 initialized)

#define isa_mmu_check(vaddr, len, type) (MMU_DIRECT)

#endif
