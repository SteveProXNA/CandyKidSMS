REM bank4
@echo off

cd ..
cd banks

folder2c bank5 bank5 5

sdcc -c --no-std-crt0 -mz80 --Werror --opt-code-speed --constseg BANK5 bank5.c

del *.asm > nul; del *.lst > nul; del *.sym > nul

cd ..
cd scripts