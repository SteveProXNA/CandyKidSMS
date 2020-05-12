REM gfx		Commonly used gfx	not banked
@echo off

cd ..
folder2c ..\psg psg

sdcc -c -mz80 --opt-code-speed --peep-file peep-rules.txt --std-c99 psg.c

del *.asm > nul; del *.lst > nul; del *.sym > nul

::cd ..
cd scripts