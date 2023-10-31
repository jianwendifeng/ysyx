<<<<<<< HEAD
include $(AM_HOME)/scripts/isa/riscv32.mk
include $(AM_HOME)/scripts/platform/nemu.mk
CFLAGS  += -DISA_H=\"riscv/riscv.h\"
=======
include $(AM_HOME)/scripts/isa/riscv.mk
include $(AM_HOME)/scripts/platform/nemu.mk
CFLAGS  += -DISA_H=\"riscv/riscv.h\"
COMMON_CFLAGS += -march=rv32im_zicsr -mabi=ilp32  # overwrite
LDFLAGS       += -melf32lriscv                     # overwrite
>>>>>>> a55e7fc7 (NJU-ProjectN/abstract-machine ics2023 initialized)

AM_SRCS += riscv/nemu/start.S \
           riscv/nemu/cte.c \
           riscv/nemu/trap.S \
           riscv/nemu/vme.c
