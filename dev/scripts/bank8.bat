REM bank8
@echo off

cd ..
cd banks

folder2c bank8 bank8 8

sdcc --debug -c --no-std-crt0 -mz80 --Werror --opt-code-speed --constseg BANK8 bank8.c

del *.asm > nul; del *.lst > nul; del *.sym > nul

cd ..
cd scripts