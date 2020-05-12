REM bank11
@echo off

cd ..
cd banks

folder2c bank11 bank11 11

sdcc -c --no-std-crt0 -mz80 --Werror --opt-code-speed --constseg BANK11 bank11.c

del *.asm > nul
del *.lst > nul
del *.sym > nul

cd ..
cd scripts