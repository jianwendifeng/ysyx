BUILD_DIR = ./build

export PATH := $(PATH):$(abspath ./utils)
SCALA_FILE = $(shell find ./playground/src -name '*.scala')

vcd ?= 
ifeq ($(vcd), 1)
	CFLAGS += -DVCD
endif
# C flags
INC_PATH += $(abspath ./sim_c/include)
INCFLAGS = $(addprefix -I, $(INC_PATH))
CFLAGS += $(INCFLAGS) $(CFLAGS_SIM) -DTOP_NAME="V$(TOPNAME)"

# source file
CSRCS = $(shell find $(abspath ./sim_c) -name "*.c" -or -name "*.cc" -or -name "*.cpp")
BIN = $(BUILD_DIR)/$(TOP)
NPC_EXEC := $(BIN)

test:
	mill -i __.test

# verilog:
# 	$(call git_commit, "generate verilog")
# 	mkdir -p $(BUILD_DIR)
# 	mill -i __.test.runMain Elaborate -td $(BUILD_DIR)

help:
	mill -i __.test.runMain Elaborate --help

compile:
	mill -i __.compile

bsp:
	mill -i mill.bsp.BSP/install

reformat:
	mill -i __.reformat

checkformat:
	mill -i __.checkFormat

clean:
	-rm -rf $(BUILD_DIR)
	-rm -rf $(BUILD_DIR) logs

.PHONY: test verilog help compile bsp reformat checkformat clean

sim:
	$(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!
# @echo "Write this Makefile by yourself."
	$(CSRCS) verilog
	@rm -rf $(OBJ_DIR)
	$(VERILATOR) $(VERILATOR_FLAGS) -top $(TOPNAME) $(CSRCS) $(wildcard $(BUILD_DIR)/verilog/*.v) \
		$(addprefix -CFLAGS , $(CFLAGS)) $(addprefix -LDFLAGS , $(LDFLAGS)) \
		--Mdir $(OBJ_DIR) -o $(abspath $(BIN))

include ../Makefile

VERILATOR = verilator
VERILATOR_COVERAGE = verilator_coverage
# verilator flags
VERILATOR_FLAGS +=  -MMD --trace --build -cc --exe \
									 -O3 --x-assign fast --x-initial fast --noassert -report-unoptflat
			
# # Disable UNUSED SIGNAL warning
# VERILATOR_FLAGS += --lint-only -Wno-UNUSED

# timescale set
VERILATOR_FLAGS += --timescale 1us/1us


verilog: $(SCALA_FILE)
	@mkdir -p $(BUILD_DIR)/verilog
	mill -i $(TOP).runMain $(MAIN) -td $(BUILD_DIR)/verilog --emit-modules verilog #--full-stacktrace


# sim: $(CSRCS) verilog
# 	@rm -rf $(OBJ_DIR)
# 	$(VERILATOR) $(VERILATOR_FLAGS) -top $(TOPNAME) $(CSRCS) $(wildcard $(BUILD_DIR)/verilog/*.v) \
# 		$(addprefix -CFLAGS , $(CFLAGS)) $(addprefix -LDFLAGS , $(LDFLAGS)) \
# 		--Mdir $(OBJ_DIR) -o $(abspath $(BIN))

run:
	@echo
	@echo "------------ RUN --------------"
	$(NPC_EXEC)
ifeq ($(vcd), 1)
	@echo "----- see vcd file in logs dir ----"
else
	@echo "----- if you need vcd file. add vcd=1 to make ----"
endif
	
srun: sim run

# clean:
# 	-rm -rf $(BUILD_DIR) logs

clean_mill:
	-rm -rf out

clean_all: clean clean_mill

.PHONY: clean clean_all clean_mill srun run sim verilog
