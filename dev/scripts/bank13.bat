REM bank13
@echo off

cd ..
cd banks

folder2c bank13 bank13 13

sdcc -c --no-std-crt0 -mz80 --Werror --opt-code-speed --constseg BANK13 bank13.c

del *.asm > nul
del *.lst > nul
del *.sym > nul

cd ..
cd scripts