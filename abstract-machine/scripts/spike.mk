<<<<<<< HEAD
include $(AM_HOME)/scripts/isa/riscv64.mk
=======
include $(AM_HOME)/scripts/isa/riscv.mk
>>>>>>> a55e7fc7 (NJU-ProjectN/abstract-machine ics2023 initialized)

AM_SRCS := riscv/spike/trm.c \
           riscv/spike/ioe.c \
           riscv/spike/timer.c \
           riscv/spike/start.S \
           riscv/spike/htif.S \
           platform/dummy/cte.c \
           platform/dummy/vme.c \
           platform/dummy/mpe.c \

CFLAGS    += -fdata-sections -ffunction-sections
LDFLAGS   += -T $(AM_HOME)/am/src/riscv/spike/linker.ld
LDFLAGS   += --gc-sections -e _start

CFLAGS += -DMAINARGS=\"$(mainargs)\"
.PHONY: $(AM_HOME)/am/src/riscv/spike/trm.c

image: $(IMAGE).elf
