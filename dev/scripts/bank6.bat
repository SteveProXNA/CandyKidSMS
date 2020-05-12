REM bank6
@echo off

cd ..
cd banks

folder2c bank6 bank6 6

sdcc -c --no-std-crt0 -mz80 --Werror --opt-code-speed --constseg BANK6 bank6.c

del *.asm > nul; del *.lst > nul; del *.sym > nul

cd ..
cd scripts