@echo off
REM Compiles the program without the C standard library

set PLATFORM_NAME=win32_shade_it
set DIST_DIR=dist

set DEF_COMPILER_FLAGS=-mconsole -march=native -mtune=native ^
-std=c89 -pedantic -nodefaultlibs -nostdlib -mno-stack-arg-probe -Xlinker /STACK:0x100000,0x100000 -Xlinker /ENTRY:mainCRTStartup ^
-fno-builtin -ffreestanding -fno-asynchronous-unwind-tables -fuse-ld=lld -fno-math-errno -fno-trapping-math ^
-Wall -Wextra -Werror -Wvla -Wconversion -Wdouble-promotion -Wsign-conversion ^
-Wmissing-field-initializers -Wuninitialized -Winit-self -Wunused -Wunused-macros -Wunused-local-typedefs

set DEF_FLAGS_LINKER=-lkernel32 -luser32 -lgdi32 -lopengl32

cc -s -O2 %DEF_COMPILER_FLAGS% %PLATFORM_NAME%.c -o %PLATFORM_NAME%.exe %DEF_FLAGS_LINKER%
%PLATFORM_NAME%.exe
