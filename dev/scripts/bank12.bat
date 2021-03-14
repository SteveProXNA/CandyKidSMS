REM bank12
@echo off

cd ..
cd banks
cd bank12

REM boss64
bmp2tile.exe raw\boss64_00.png -savetiles "boss64_00 (tiles).psgcompr" -noremovedupes -nomirror -planar -tileoffset 0 -savepalette "boss64_00 (palette).bin" -fullpalette -spritepalette -exit
bmp2tile.exe raw\boss64_01.png -savetiles "boss64_01 (tiles).psgcompr" -noremovedupes -nomirror -planar -tileoffset 0 -savepalette "boss64_01 (palette).bin" -fullpalette -spritepalette -exit
bmp2tile.exe raw\boss64_02.png -savetiles "boss64_02 (tiles).psgcompr" -noremovedupes -nomirror -planar -tileoffset 0 -savepalette "boss64_02 (palette).bin" -fullpalette -spritepalette -exit

cd ..
folder2c bank12 bank12 12

sdcc --debug -c --no-std-crt0 -mz80 --Werror --opt-code-speed --constseg BANK12 bank12.c

del *.asm > nul; del *.lst > nul; del *.sym > nul

cd ..
cd scripts