# Targets:
# # all
# # # receiver
# # # transmitter
# # runReceiver
# # runTransmitter

CC := g++
CFLAGS := -O3
LDFLAGS := -lwiringPi
EXEC := execute.out

# OBJDIR MUST BE SET AND SET NOT TO A DIRECTORY
# CONTAINING IMPORTANT FILES !! SEE TARGET `CLEAN` FOR REASONING
OBJDIR := .ObjectFiles/
BASE_OBJS := \
	$(OBJDIR)Setters.o \
	$(OBJDIR)Miscellaneous.o \
	$(OBJDIR)WOR.o \
	$(OBJDIR)SPI.o \
	$(OBJDIR)Debug.o \
	$(OBJDIR)Packets.o \
	$(OBJDIR)Settings.o \
	$(OBJDIR)Control.o \


all: receiver transmitter

R_MAIN := $(OBJDIR)RX_Demo.o
R_EXEC := RX_Demo.out
receiver: $(BASE_OBJS) $(R_MAIN)
	sudo $(CC) $(BASE_OBJS) $(R_MAIN) -o $(R_EXEC) $(LDFLAGS)
testReceiver: receiver
	sudo ./$(R_EXEC) -v -a3 -c1 -f434 -m100
runReceiver: receiver
	sudo ./$(R_EXEC) -a3 -c1 -f434 -m100 2>R_err.log

T_MAIN := $(OBJDIR)TX_Demo.o
T_EXEC := TX_Demo.out
transmitter: $(BASE_OBJS) $(T_MAIN)
	sudo $(CC) $(BASE_OBJS) $(T_MAIN) -o $(T_EXEC) $(LDFLAGS)
testTransmitter: transmitter
	sudo ./$(T_EXEC) -v -a1 -r3 -i1000 -t5 -c1 -f434 -m100
runTransmitter: transmitter
	sudo ./$(T_EXEC) -a1 -r3 -i1000 -t0 -c1 -f434 -m100 2>T_err.log

$(OBJDIR)Setters.o: lib/Setters.cpp /usr/include/stdc-predef.h lib/CC1100.hpp \
 /usr/include/stdio.h /usr/include/features.h \
 /usr/include/arm-linux-gnueabihf/sys/cdefs.h \
 /usr/include/arm-linux-gnueabihf/bits/wordsize.h \
 /usr/include/arm-linux-gnueabihf/gnu/stubs.h \
 /usr/include/arm-linux-gnueabihf/gnu/stubs-hard.h \
 /usr/lib/gcc/arm-linux-gnueabihf/6/include/stddef.h \
 /usr/include/arm-linux-gnueabihf/bits/types.h \
 /usr/include/arm-linux-gnueabihf/bits/typesizes.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/wchar.h \
 /usr/lib/gcc/arm-linux-gnueabihf/6/include/stdarg.h \
 /usr/include/arm-linux-gnueabihf/bits/stdio_lim.h \
 /usr/include/arm-linux-gnueabihf/bits/sys_errlist.h \
 /usr/lib/gcc/arm-linux-gnueabihf/6/include/stdint.h \
 /usr/include/stdint.h /usr/include/arm-linux-gnueabihf/bits/wchar.h \
 /usr/include/string.h /usr/include/xlocale.h \
 /usr/local/include/wiringPi.h /usr/local/include/wiringPiSPI.h \
 lib/Macros.hpp
	sudo $(CC) -c $< -o $@ $(CFLAGS)
$(OBJDIR)Miscellaneous.o: lib/Miscellaneous.cpp /usr/include/stdc-predef.h \
 lib/CC1100.hpp /usr/include/stdio.h /usr/include/features.h \
 /usr/include/arm-linux-gnueabihf/sys/cdefs.h \
 /usr/include/arm-linux-gnueabihf/bits/wordsize.h \
 /usr/include/arm-linux-gnueabihf/gnu/stubs.h \
 /usr/include/arm-linux-gnueabihf/gnu/stubs-hard.h \
 /usr/lib/gcc/arm-linux-gnueabihf/6/include/stddef.h \
 /usr/include/arm-linux-gnueabihf/bits/types.h \
 /usr/include/arm-linux-gnueabihf/bits/typesizes.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/wchar.h \
 /usr/lib/gcc/arm-linux-gnueabihf/6/include/stdarg.h \
 /usr/include/arm-linux-gnueabihf/bits/stdio_lim.h \
 /usr/include/arm-linux-gnueabihf/bits/sys_errlist.h \
 /usr/lib/gcc/arm-linux-gnueabihf/6/include/stdint.h \
 /usr/include/stdint.h /usr/include/arm-linux-gnueabihf/bits/wchar.h \
 /usr/include/string.h /usr/include/xlocale.h \
 /usr/local/include/wiringPi.h /usr/local/include/wiringPiSPI.h \
 lib/Macros.hpp
	sudo $(CC) -c $< -o $@ $(CFLAGS)
$(OBJDIR)WOR.o: lib/WOR.cpp /usr/include/stdc-predef.h lib/CC1100.hpp \
 /usr/include/stdio.h /usr/include/features.h \
 /usr/include/arm-linux-gnueabihf/sys/cdefs.h \
 /usr/include/arm-linux-gnueabihf/bits/wordsize.h \
 /usr/include/arm-linux-gnueabihf/gnu/stubs.h \
 /usr/include/arm-linux-gnueabihf/gnu/stubs-hard.h \
 /usr/lib/gcc/arm-linux-gnueabihf/6/include/stddef.h \
 /usr/include/arm-linux-gnueabihf/bits/types.h \
 /usr/include/arm-linux-gnueabihf/bits/typesizes.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/wchar.h \
 /usr/lib/gcc/arm-linux-gnueabihf/6/include/stdarg.h \
 /usr/include/arm-linux-gnueabihf/bits/stdio_lim.h \
 /usr/include/arm-linux-gnueabihf/bits/sys_errlist.h \
 /usr/lib/gcc/arm-linux-gnueabihf/6/include/stdint.h \
 /usr/include/stdint.h /usr/include/arm-linux-gnueabihf/bits/wchar.h \
 /usr/include/string.h /usr/include/xlocale.h \
 /usr/local/include/wiringPi.h /usr/local/include/wiringPiSPI.h \
 lib/Macros.hpp
	sudo $(CC) -c $< -o $@ $(CFLAGS)
$(OBJDIR)SPI.o: lib/SPI.cpp /usr/include/stdc-predef.h lib/CC1100.hpp \
 /usr/include/stdio.h /usr/include/features.h \
 /usr/include/arm-linux-gnueabihf/sys/cdefs.h \
 /usr/include/arm-linux-gnueabihf/bits/wordsize.h \
 /usr/include/arm-linux-gnueabihf/gnu/stubs.h \
 /usr/include/arm-linux-gnueabihf/gnu/stubs-hard.h \
 /usr/lib/gcc/arm-linux-gnueabihf/6/include/stddef.h \
 /usr/include/arm-linux-gnueabihf/bits/types.h \
 /usr/include/arm-linux-gnueabihf/bits/typesizes.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/wchar.h \
 /usr/lib/gcc/arm-linux-gnueabihf/6/include/stdarg.h \
 /usr/include/arm-linux-gnueabihf/bits/stdio_lim.h \
 /usr/include/arm-linux-gnueabihf/bits/sys_errlist.h \
 /usr/lib/gcc/arm-linux-gnueabihf/6/include/stdint.h \
 /usr/include/stdint.h /usr/include/arm-linux-gnueabihf/bits/wchar.h \
 /usr/include/string.h /usr/include/xlocale.h \
 /usr/local/include/wiringPi.h /usr/local/include/wiringPiSPI.h \
 lib/Macros.hpp
	sudo $(CC) -c $< -o $@ $(CFLAGS)
$(OBJDIR)Debug.o: lib/Debug.cpp /usr/include/stdc-predef.h lib/CC1100.hpp \
 /usr/include/stdio.h /usr/include/features.h \
 /usr/include/arm-linux-gnueabihf/sys/cdefs.h \
 /usr/include/arm-linux-gnueabihf/bits/wordsize.h \
 /usr/include/arm-linux-gnueabihf/gnu/stubs.h \
 /usr/include/arm-linux-gnueabihf/gnu/stubs-hard.h \
 /usr/lib/gcc/arm-linux-gnueabihf/6/include/stddef.h \
 /usr/include/arm-linux-gnueabihf/bits/types.h \
 /usr/include/arm-linux-gnueabihf/bits/typesizes.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/wchar.h \
 /usr/lib/gcc/arm-linux-gnueabihf/6/include/stdarg.h \
 /usr/include/arm-linux-gnueabihf/bits/stdio_lim.h \
 /usr/include/arm-linux-gnueabihf/bits/sys_errlist.h \
 /usr/lib/gcc/arm-linux-gnueabihf/6/include/stdint.h \
 /usr/include/stdint.h /usr/include/arm-linux-gnueabihf/bits/wchar.h \
 /usr/include/string.h /usr/include/xlocale.h \
 /usr/local/include/wiringPi.h /usr/local/include/wiringPiSPI.h \
 lib/Macros.hpp
	sudo $(CC) -c $< -o $@ $(CFLAGS)
$(OBJDIR)Packets.o: lib/Packets.cpp /usr/include/stdc-predef.h lib/CC1100.hpp \
 /usr/include/stdio.h /usr/include/features.h \
 /usr/include/arm-linux-gnueabihf/sys/cdefs.h \
 /usr/include/arm-linux-gnueabihf/bits/wordsize.h \
 /usr/include/arm-linux-gnueabihf/gnu/stubs.h \
 /usr/include/arm-linux-gnueabihf/gnu/stubs-hard.h \
 /usr/lib/gcc/arm-linux-gnueabihf/6/include/stddef.h \
 /usr/include/arm-linux-gnueabihf/bits/types.h \
 /usr/include/arm-linux-gnueabihf/bits/typesizes.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/wchar.h \
 /usr/lib/gcc/arm-linux-gnueabihf/6/include/stdarg.h \
 /usr/include/arm-linux-gnueabihf/bits/stdio_lim.h \
 /usr/include/arm-linux-gnueabihf/bits/sys_errlist.h \
 /usr/lib/gcc/arm-linux-gnueabihf/6/include/stdint.h \
 /usr/include/stdint.h /usr/include/arm-linux-gnueabihf/bits/wchar.h \
 /usr/include/string.h /usr/include/xlocale.h \
 /usr/local/include/wiringPi.h /usr/local/include/wiringPiSPI.h \
 lib/Macros.hpp
	sudo $(CC) -c $< -o $@ $(CFLAGS)
$(OBJDIR)Settings.o: lib/Settings.cpp /usr/include/stdc-predef.h lib/CC1100.hpp \
 /usr/include/stdio.h /usr/include/features.h \
 /usr/include/arm-linux-gnueabihf/sys/cdefs.h \
 /usr/include/arm-linux-gnueabihf/bits/wordsize.h \
 /usr/include/arm-linux-gnueabihf/gnu/stubs.h \
 /usr/include/arm-linux-gnueabihf/gnu/stubs-hard.h \
 /usr/lib/gcc/arm-linux-gnueabihf/6/include/stddef.h \
 /usr/include/arm-linux-gnueabihf/bits/types.h \
 /usr/include/arm-linux-gnueabihf/bits/typesizes.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/wchar.h \
 /usr/lib/gcc/arm-linux-gnueabihf/6/include/stdarg.h \
 /usr/include/arm-linux-gnueabihf/bits/stdio_lim.h \
 /usr/include/arm-linux-gnueabihf/bits/sys_errlist.h \
 /usr/lib/gcc/arm-linux-gnueabihf/6/include/stdint.h \
 /usr/include/stdint.h /usr/include/arm-linux-gnueabihf/bits/wchar.h \
 /usr/include/string.h /usr/include/xlocale.h \
 /usr/local/include/wiringPi.h /usr/local/include/wiringPiSPI.h \
 lib/Macros.hpp
	sudo $(CC) -c $< -o $@ $(CFLAGS)
$(OBJDIR)Control.o: lib/Control.cpp /usr/include/stdc-predef.h lib/CC1100.hpp \
 /usr/include/stdio.h /usr/include/features.h \
 /usr/include/arm-linux-gnueabihf/sys/cdefs.h \
 /usr/include/arm-linux-gnueabihf/bits/wordsize.h \
 /usr/include/arm-linux-gnueabihf/gnu/stubs.h \
 /usr/include/arm-linux-gnueabihf/gnu/stubs-hard.h \
 /usr/lib/gcc/arm-linux-gnueabihf/6/include/stddef.h \
 /usr/include/arm-linux-gnueabihf/bits/types.h \
 /usr/include/arm-linux-gnueabihf/bits/typesizes.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/wchar.h \
 /usr/lib/gcc/arm-linux-gnueabihf/6/include/stdarg.h \
 /usr/include/arm-linux-gnueabihf/bits/stdio_lim.h \
 /usr/include/arm-linux-gnueabihf/bits/sys_errlist.h \
 /usr/lib/gcc/arm-linux-gnueabihf/6/include/stdint.h \
 /usr/include/stdint.h /usr/include/arm-linux-gnueabihf/bits/wchar.h \
 /usr/include/string.h /usr/include/xlocale.h \
 /usr/local/include/wiringPi.h /usr/local/include/wiringPiSPI.h \
 lib/Macros.hpp
	sudo $(CC) -c $< -o $@ $(CFLAGS)
$(OBJDIR)RX_Demo.o: RX_Demo.cpp /usr/include/stdc-predef.h lib/CC1100.hpp \
 /usr/include/stdio.h /usr/include/features.h \
 /usr/include/arm-linux-gnueabihf/sys/cdefs.h \
 /usr/include/arm-linux-gnueabihf/bits/wordsize.h \
 /usr/include/arm-linux-gnueabihf/gnu/stubs.h \
 /usr/include/arm-linux-gnueabihf/gnu/stubs-hard.h \
 /usr/lib/gcc/arm-linux-gnueabihf/6/include/stddef.h \
 /usr/include/arm-linux-gnueabihf/bits/types.h \
 /usr/include/arm-linux-gnueabihf/bits/typesizes.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/wchar.h \
 /usr/lib/gcc/arm-linux-gnueabihf/6/include/stdarg.h \
 /usr/include/arm-linux-gnueabihf/bits/stdio_lim.h \
 /usr/include/arm-linux-gnueabihf/bits/sys_errlist.h \
 /usr/lib/gcc/arm-linux-gnueabihf/6/include/stdint.h \
 /usr/include/stdint.h /usr/include/arm-linux-gnueabihf/bits/wchar.h \
 /usr/include/string.h /usr/include/xlocale.h \
 /usr/local/include/wiringPi.h /usr/local/include/wiringPiSPI.h \
 /usr/include/c++/6/stdlib.h /usr/include/c++/6/cstdlib \
 /usr/include/arm-linux-gnueabihf/c++/6/bits/c++config.h \
 /usr/include/arm-linux-gnueabihf/c++/6/bits/os_defines.h \
 /usr/include/arm-linux-gnueabihf/c++/6/bits/cpu_defines.h \
 /usr/include/stdlib.h /usr/include/arm-linux-gnueabihf/bits/waitflags.h \
 /usr/include/arm-linux-gnueabihf/bits/waitstatus.h \
 /usr/include/arm-linux-gnueabihf/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/arm-linux-gnueabihf/bits/endian.h \
 /usr/include/arm-linux-gnueabihf/bits/byteswap.h \
 /usr/include/arm-linux-gnueabihf/bits/byteswap-16.h \
 /usr/include/arm-linux-gnueabihf/sys/select.h \
 /usr/include/arm-linux-gnueabihf/bits/select.h \
 /usr/include/arm-linux-gnueabihf/bits/sigset.h \
 /usr/include/arm-linux-gnueabihf/bits/time.h \
 /usr/include/arm-linux-gnueabihf/sys/sysmacros.h \
 /usr/include/arm-linux-gnueabihf/bits/pthreadtypes.h \
 /usr/include/alloca.h \
 /usr/include/arm-linux-gnueabihf/bits/stdlib-float.h \
 /usr/include/getopt.h lib/Macros.hpp
	sudo $(CC) -c $< -o $@ $(CFLAGS)
$(OBJDIR)TX_Demo.o: TX_Demo.cpp /usr/include/stdc-predef.h lib/CC1100.hpp \
 /usr/include/stdio.h /usr/include/features.h \
 /usr/include/arm-linux-gnueabihf/sys/cdefs.h \
 /usr/include/arm-linux-gnueabihf/bits/wordsize.h \
 /usr/include/arm-linux-gnueabihf/gnu/stubs.h \
 /usr/include/arm-linux-gnueabihf/gnu/stubs-hard.h \
 /usr/lib/gcc/arm-linux-gnueabihf/6/include/stddef.h \
 /usr/include/arm-linux-gnueabihf/bits/types.h \
 /usr/include/arm-linux-gnueabihf/bits/typesizes.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/wchar.h \
 /usr/lib/gcc/arm-linux-gnueabihf/6/include/stdarg.h \
 /usr/include/arm-linux-gnueabihf/bits/stdio_lim.h \
 /usr/include/arm-linux-gnueabihf/bits/sys_errlist.h \
 /usr/lib/gcc/arm-linux-gnueabihf/6/include/stdint.h \
 /usr/include/stdint.h /usr/include/arm-linux-gnueabihf/bits/wchar.h \
 /usr/include/string.h /usr/include/xlocale.h \
 /usr/local/include/wiringPi.h /usr/local/include/wiringPiSPI.h \
 /usr/include/c++/6/stdlib.h /usr/include/c++/6/cstdlib \
 /usr/include/arm-linux-gnueabihf/c++/6/bits/c++config.h \
 /usr/include/arm-linux-gnueabihf/c++/6/bits/os_defines.h \
 /usr/include/arm-linux-gnueabihf/c++/6/bits/cpu_defines.h \
 /usr/include/stdlib.h /usr/include/arm-linux-gnueabihf/bits/waitflags.h \
 /usr/include/arm-linux-gnueabihf/bits/waitstatus.h \
 /usr/include/arm-linux-gnueabihf/sys/types.h /usr/include/time.h \
 /usr/include/endian.h /usr/include/arm-linux-gnueabihf/bits/endian.h \
 /usr/include/arm-linux-gnueabihf/bits/byteswap.h \
 /usr/include/arm-linux-gnueabihf/bits/byteswap-16.h \
 /usr/include/arm-linux-gnueabihf/sys/select.h \
 /usr/include/arm-linux-gnueabihf/bits/select.h \
 /usr/include/arm-linux-gnueabihf/bits/sigset.h \
 /usr/include/arm-linux-gnueabihf/bits/time.h \
 /usr/include/arm-linux-gnueabihf/sys/sysmacros.h \
 /usr/include/arm-linux-gnueabihf/bits/pthreadtypes.h \
 /usr/include/alloca.h \
 /usr/include/arm-linux-gnueabihf/bits/stdlib-float.h \
 /usr/include/getopt.h lib/Macros.hpp
	sudo $(CC) -c $< -o $@ $(CFLAGS)
clean:
	rm -f $(OBJDIR)/* $(R_EXEC) $(T_EXEC)
