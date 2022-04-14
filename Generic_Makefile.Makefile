# CC stands for CrossCompiler. Here, we point the CC towards the cross compiling toolchain that we intend to use

CC=arm-none-eabi-gcc

# CFLAGS stands for CompilerFlags. Here, we instruct the flags that instruct the compiler on its input output behavior
# -mcpu=cortex-m4 => Necessary to avoid defualt settings of the compiler
# -mthumb => Necessary to avoid ARM instructions being compiled ( default being ARM instructions)
# -std=gnu11 => Necessary to instruct compiler to adhere to GNU dialect ISO C11
# -O0 => No optimiztion necessary 
# -c => Could be added for only compilation into O files instead of linker invokation (Only debugging)
# -Wall => Turn on all availble warnings
# -mfloat-abi => To specify GCC to generate appropriate library function calls for floating point operations

CFLAGS= -mcpu=cortex-m4 -mthumb -std=gnu11 -O0 -c -Wall -mfloat-abi=soft

# LDFLAGS stands for LinkerFlags. We instruct the flags for compiler linker co-operation
# -nostdlib => Necessary to disable inclusion of any default/standard C Runtime library ( Used mostly for IO)
# -T => Flag to point to the linkerscript 
# -Map => Flag to instruct linker to create linker map
# -Wl, => Used to specify that the following command is a linker command
# -mcpu=cortex-m4 => Linker links with Newlib nano and hence it needs to know about the target as well
# -mthumb => Linker links with Newlib nano and hence it needs to know about the target as well
# nano.specs => Necessary when Newlib Nano C Standard runtime library is necessary. Be sure to include system calls file
# nosys.specs => Necessary when no system calls file is included inside the project
# rdimon.specs => Necessary for semihosting. Syscalls should not be linked as the library does that by itself.
# -mfloat-abi => To specify GCC to generate appropriate library function calls for floating point operations

# all => target command to recursively call any target that we require
# $^ denotes all dependencies
# $@ denotes all targets
# Example recipe ( recipe needs two tabs after the first line)
# Main.o:main.c  ( First .o is target and : is followd by dependency)
#   $(CC) $(CFLAGS) Main.o -o main.c    ( Main.o and main.c are replaced by shortcuts $^ and $@)

LDFLAGS= -mcpu=cortex-m4 -mthumb --specs=nano.specs -T LinkerScript.ld -Wl,-Map=Final.map -mfloat-abi=soft

LDFLAGS_SEMIHOSTING= -mcpu=cortex-m4 -mthumb --specs=rdimon.specs -T LinkerScript.ld -Wl,-Map=Final.map -mfloat-abi=soft

all:Final.elf Final_Semihosting.elf ELF-h 

Main.o:main.c
    $(CC) $(CFLAGS) $^ -o $@

Startup.o:CortexM4_Startup_C.c
    $(CC) $(CFLAGS) $^ -o $@

Syscalls.o:syscalls.c
    $(CC) $(CFLAGS) $^ -o $@

Final.elf:Main.o Startup.o Syscalls.o 
    $(CC) $(LDFLAGS) $^ -o $@

Final_Semihosting.elf:Main.o Startup.o 
    $(CC) $(LDFLAGS_SEMIHOSTING) $^ -o $@

clean:
    rm *.o *.elf *.map

load:
    openocd -f board/st_nucleo_f4.cfg

ELF-h:
    arm-none-eabi-objdump -h Final.elf

ELF-d:
    arm-none-eabi-objdump -d Final.elf