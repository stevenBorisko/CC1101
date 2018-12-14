BASE_PATH := $(dir $(realpath $(lastword $(MAKEFILE_LIST))))


# --- Definitions ---

# This object does not correspond to an implementation file,
#     especially not a file with `main` in it
# This object will be BASE_SUB_OBJS and all OTHER_MAIN_OBJs
#     linked together
BASE_MAIN_OBJ := $(BASE_PATH)Base.o

# Flags for compiling and linking
BASE_CFLAGS := -O3
BASE_LFLAGS :=

# This is where the BASE_SUB_OBJS will be stored so your work doesn't
#     get cluttered with *.o files
_BASE_OBJDIR := .ObjectFiles/
BASE_OBJDIR := $(BASE_PATH)$(_BASE_OBJDIR)

# Files on which all the implementation files depend
_BASE_DEPS := CC1100.hpp Macros.hpp
BASE_DEPS := $(foreach OBJ,$(_BASE_DEPS),$(BASE_PATH)$(OBJ))

# All implementation files to be compiled for the BASE_MAIN_OBJ
_BASE_SUB_OBJS := \
	Setters.o \
	Miscellaneous.o \
	WOR.o \
	SPI.o \
	Debug.o \
	Packets.o \
	Settings.o \
	Control.o
BASE_SUB_OBJS := $(foreach OBJ,$(_BASE_SUB_OBJS),$(BASE_OBJDIR)$(OBJ))

# --- Rules ---

# Main object
# Links object files into one object file (BASE_MAIN_OBJ)
# Also
$(BASE_MAIN_OBJ): $(BASE_SUB_OBJS)
	@echo "- - - - Base compiled - - - -"
	$(LD) -r $(BASE_LFLAGS) $^ -o $@
	@echo "- - - - Base linked - - - -"

# Sub objects
# Compile implementation file
$(BASE_OBJDIR)%.o: $(BASE_PATH)%.cpp $(BASE_DEPS)
	$(CC) -c $(BASE_CFLAGS) $< -o $@

# Object Directory Creation
# This creates the object directory for Base and the directory for Other
BaseObjectDirectory:
	mkdir -p $(BASE_OBJDIR)
	@echo "- - - - Base ObjectFile directory created - - - -"

# Clean
# Removes all object directories from Base and Other
BaseClean:
	rm -f $(BASE_SUB_OBJS) $(BASE_MAIN_OBJ)
