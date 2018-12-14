# Targets:
# # all
# # # receiver
# # # transmitter
# # runReceiver
# # runTransmitter

all: receiver transmitter
	@echo "- - - - Project compiled - - - -"

MAIN_PATH := $(dir $(realpath $(lastword $(MAKEFILE_LIST))))
include $(MAIN_PATH)/lib/Base.mk

# MAIN VARIABLES

CC := g++
CFLAGS := -O3
LDFLAGS := -lwiringPi

# OTHER VARIABLES

_MAIN_OBJDIR := .ObjectFiles/
MAIN_OBJDIR := $(MAIN_PATH)$(_MAIN_OBJDIR)

_OTHER_SUB_OBJS := lib/Base.o
OTHER_SUB_OBJS := $(foreach OBJ,$(_OTHER_SUB_OBJS),$(MAIN_PATH)$(OBJ))

_MAIN_DEPS := lib/CC1100.hpp lib/Macros.hpp
MAIN_DEPS := $(foreach OBJ,$(_MAIN_DEPS),$(MAIN_PATH)$(OBJ))

# MAKE MAINS

R_MAIN := $(MAIN_OBJDIR)RX_Demo.o
R_EXEC := RX_Demo.out
R_ERR := R_err.log
receiver: $(OTHER_SUB_OBJS) $(R_MAIN)
	sudo $(CC) $(OTHER_SUB_OBJS) $(R_MAIN) -o $(R_EXEC) $(LDFLAGS)
	@echo "- - - - Receiver compiled - - - -"
	@echo "Executable $(R_EXEC)"
testReceiver: receiver
	sudo ./$(R_EXEC) -v -a3 -c1 -f434 -m100
runReceiver: receiver
	sudo ./$(R_EXEC) -a3 -c1 -f434 -m100 2>$(R_ERR)

T_MAIN := $(MAIN_OBJDIR)TX_Demo.o
T_EXEC := TX_Demo.out
T_ERR := T_err.log
transmitter: $(OTHER_SUB_OBJS) $(T_MAIN)
	sudo $(CC) $(OTHER_SUB_OBJS) $(T_MAIN) -o $(T_EXEC) $(LDFLAGS)
	@echo "- - - - Transmitter compiled - - - -"
	@echo "Executable $(T_EXEC)"
testTransmitter: transmitter
	sudo ./$(T_EXEC) -v -a1 -r3 -i1000 -t5 -c1 -f434 -m100
runTransmitter: transmitter
	sudo ./$(T_EXEC) -a1 -r3 -i1000 -t0 -c1 -f434 -m100 2>$(T_ERR)

# COMPILE MAIN

$(MAIN_OBJDIR)%.o: %.cpp $(MAIN_DEPS)
	$(CC) -c $(CFLAGS) $< -o $@

# OBJECT FILE DIRECTORY

ObjectDirectory: BaseObjectDirectory
	mkdir -p  $(MAIN_OBJDIR)
	@echo "- - - - Main ObjectFile directory created - - - -"

# CLEAN

clean: BaseClean cleanReceiver cleanTransmitter

cleanReceiver:
	rm -f $(R_MAIN) $(R_EXEC) $(R_ERR)

cleanTransmitter:
	rm -f $(T_MAIN) $(T_EXEC) $(T_ERR)
