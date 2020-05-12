REM bank14
@echo off

cd ..
cd banks

folder2c bank14 bank14 14

sdcc -c --no-std-crt0 -mz80 --Werror --opt-code-speed --constseg BANK14 bank14.c

del *.asm > nul; del *.lst > nul; del *.sym > nul

cd ..
cd scripts