REM bank13
@echo off

cd ..
cd banks
cd bank13

REM boss64
bmp2tile.exe raw\boss64_03.png -savetiles "boss64_03 (tiles).psgcompr" -noremovedupes -nomirror -planar -tileoffset 0 -savepalette "boss64_03 (palette).bin" -fullpalette -spritepalette -exit
bmp2tile.exe raw\boss64_04.png -savetiles "boss64_04 (tiles).psgcompr" -noremovedupes -nomirror -planar -tileoffset 0 -savepalette "boss64_04 (palette).bin" -fullpalette -spritepalette -exit
bmp2tile.exe raw\boss64_05.png -savetiles "boss64_05 (tiles).psgcompr" -noremovedupes -nomirror -planar -tileoffset 0 -savepalette "boss64_05 (palette).bin" -fullpalette -spritepalette -exit

cd ..
folder2c bank13 bank13 13

sdcc --debug -c --no-std-crt0 -mz80 --Werror --opt-code-speed --constseg BANK13 bank13.c

del *.asm > nul; del *.lst > nul; del *.sym > nul

cd ..
cd scripts