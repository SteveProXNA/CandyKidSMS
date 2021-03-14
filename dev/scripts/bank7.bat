REM bank6
@echo off

cd ..
cd banks

folder2c bank7 bank7 7

sdcc --debug -c --no-std-crt0 -mz80 --Werror --opt-code-speed --constseg BANK7 bank7.c

del *.asm > nul; del *.lst > nul; del *.sym > nul

cd ..
cd scripts