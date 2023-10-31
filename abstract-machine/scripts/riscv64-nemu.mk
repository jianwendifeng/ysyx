<<<<<<< HEAD
include $(AM_HOME)/scripts/isa/riscv64.mk
=======
include $(AM_HOME)/scripts/isa/riscv.mk
>>>>>>> a55e7fc7 (NJU-ProjectN/abstract-machine ics2023 initialized)
include $(AM_HOME)/scripts/platform/nemu.mk
CFLAGS  += -DISA_H=\"riscv/riscv.h\"

AM_SRCS += riscv/nemu/start.S \
           riscv/nemu/cte.c \
           riscv/nemu/trap.S \
           riscv/nemu/vme.c
