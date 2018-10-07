CC := g++
CFLAGS := -O3
LDFLAGS := -lwiringPi

# OBJDIR MUST BE SET AND SET NOT TO A DIRECTORY
# CONTAINING IMPORTANT FILES !! SEE TARGET `CLEAN` FOR REASONING
OBJDIR := .ObjectFiles/

# Transmitter

T_OBJS := \
	$(OBJDIR)cc1100_raspi.o \
	$(OBJDIR)TX_Demo.o \
T_EXEC := TX_Demo
transmitter: $(T_OBJS)
	sudo $(CC) $(T_OBJS) -o $(T_EXEC) $(LDFLAGS)
runTransmitter: compile
	sudo ./TX_Demo -v -a1 -r3 -i1000 -t5 -c1 -f434 -m100

# Receiver

R_OBJS := \
	$(OBJDIR)cc1100_raspi.o \
	$(OBJDIR)RX_Demo.o \
R_EXEC := RX_Demo
receiver: $(R_OBJS)
	sudo $(CC) $(T_OBJS) -o $(R_EXEC) $(LDFLAGS)
runReveiver: compile
	sudo ./RX_Demo -v -a3 -c1 -f434 -m100

# Per file compilation rules

$(OBJDIR)cc1100_raspi.o: cc1100_raspi.cpp /usr/include/stdc-predef.h \
 cc1100_raspi.h /usr/lib/gcc/arm-linux-gnueabihf/6/include/stdint.h \
 /usr/include/stdint.h /usr/include/features.h \
 /usr/include/arm-linux-gnueabihf/sys/cdefs.h \
 /usr/include/arm-linux-gnueabihf/bits/wordsize.h \
 /usr/include/arm-linux-gnueabihf/gnu/stubs.h \
 /usr/include/arm-linux-gnueabihf/gnu/stubs-hard.h \
 /usr/include/arm-linux-gnueabihf/bits/wchar.h /usr/include/stdio.h \
 /usr/lib/gcc/arm-linux-gnueabihf/6/include/stddef.h \
 /usr/include/arm-linux-gnueabihf/bits/types.h \
 /usr/include/arm-linux-gnueabihf/bits/typesizes.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/wchar.h \
 /usr/lib/gcc/arm-linux-gnueabihf/6/include/stdarg.h \
 /usr/include/arm-linux-gnueabihf/bits/stdio_lim.h \
 /usr/include/arm-linux-gnueabihf/bits/sys_errlist.h \
 /usr/include/string.h /usr/include/xlocale.h \
 /usr/local/include/wiringPi.h /usr/local/include/wiringPiSPI.h
	sudo $(CC) -c $< -o $@ $(CFLAGS)
$(OBJDIR)RX_Demo.o: RX_Demo.cpp /usr/include/stdc-predef.h cc1100_raspi.h \
 /usr/lib/gcc/arm-linux-gnueabihf/6/include/stdint.h \
 /usr/include/stdint.h /usr/include/features.h \
 /usr/include/arm-linux-gnueabihf/sys/cdefs.h \
 /usr/include/arm-linux-gnueabihf/bits/wordsize.h \
 /usr/include/arm-linux-gnueabihf/gnu/stubs.h \
 /usr/include/arm-linux-gnueabihf/gnu/stubs-hard.h \
 /usr/include/arm-linux-gnueabihf/bits/wchar.h /usr/include/stdio.h \
 /usr/lib/gcc/arm-linux-gnueabihf/6/include/stddef.h \
 /usr/include/arm-linux-gnueabihf/bits/types.h \
 /usr/include/arm-linux-gnueabihf/bits/typesizes.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/wchar.h \
 /usr/lib/gcc/arm-linux-gnueabihf/6/include/stdarg.h \
 /usr/include/arm-linux-gnueabihf/bits/stdio_lim.h \
 /usr/include/arm-linux-gnueabihf/bits/sys_errlist.h \
 /usr/include/c++/6/stdlib.h /usr/include/c++/6/cstdlib \
 /usr/include/arm-linux-gnueabihf/c++/6/bits/c++config.h \
 /usr/include/arm-linux-gnueabihf/c++/6/bits/os_defines.h \
 /usr/include/arm-linux-gnueabihf/c++/6/bits/cpu_defines.h \
 /usr/include/stdlib.h /usr/include/arm-linux-gnueabihf/bits/waitflags.h \
 /usr/include/arm-linux-gnueabihf/bits/waitstatus.h \
 /usr/include/xlocale.h /usr/include/arm-linux-gnueabihf/sys/types.h \
 /usr/include/time.h /usr/include/endian.h \
 /usr/include/arm-linux-gnueabihf/bits/endian.h \
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
 /usr/include/string.h /usr/include/getopt.h \
 /usr/local/include/wiringPi.h /usr/local/include/wiringPiSPI.h
	sudo $(CC) -c $< -o $@ $(CFLAGS)
$(OBJDIR)TX_Demo.o: TX_Demo.cpp /usr/include/stdc-predef.h cc1100_raspi.h \
 /usr/lib/gcc/arm-linux-gnueabihf/6/include/stdint.h \
 /usr/include/stdint.h /usr/include/features.h \
 /usr/include/arm-linux-gnueabihf/sys/cdefs.h \
 /usr/include/arm-linux-gnueabihf/bits/wordsize.h \
 /usr/include/arm-linux-gnueabihf/gnu/stubs.h \
 /usr/include/arm-linux-gnueabihf/gnu/stubs-hard.h \
 /usr/include/arm-linux-gnueabihf/bits/wchar.h /usr/include/stdio.h \
 /usr/lib/gcc/arm-linux-gnueabihf/6/include/stddef.h \
 /usr/include/arm-linux-gnueabihf/bits/types.h \
 /usr/include/arm-linux-gnueabihf/bits/typesizes.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/wchar.h \
 /usr/lib/gcc/arm-linux-gnueabihf/6/include/stdarg.h \
 /usr/include/arm-linux-gnueabihf/bits/stdio_lim.h \
 /usr/include/arm-linux-gnueabihf/bits/sys_errlist.h \
 /usr/include/c++/6/stdlib.h /usr/include/c++/6/cstdlib \
 /usr/include/arm-linux-gnueabihf/c++/6/bits/c++config.h \
 /usr/include/arm-linux-gnueabihf/c++/6/bits/os_defines.h \
 /usr/include/arm-linux-gnueabihf/c++/6/bits/cpu_defines.h \
 /usr/include/stdlib.h /usr/include/arm-linux-gnueabihf/bits/waitflags.h \
 /usr/include/arm-linux-gnueabihf/bits/waitstatus.h \
 /usr/include/xlocale.h /usr/include/arm-linux-gnueabihf/sys/types.h \
 /usr/include/time.h /usr/include/endian.h \
 /usr/include/arm-linux-gnueabihf/bits/endian.h \
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
 /usr/include/string.h /usr/include/getopt.h \
 /usr/local/include/wiringPi.h /usr/local/include/wiringPiSPI.h
	sudo $(CC) -c $< -o $@ $(CFLAGS)
clean:
	rm -f $(OBJDIR)/* $(EXEC)
