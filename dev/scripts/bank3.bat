REM bank3
@echo off

cd ..
cd banks
cd bank3

REM boss32
bmp2tile.exe raw\boss32_00.png -savetiles "boss32_00 (tiles).psgcompr" -noremovedupes -nomirror -planar -tileoffset 0 -savepalette "boss32_00 (palette).bin" -fullpalette -spritepalette -exit
bmp2tile.exe raw\boss32_01.png -savetiles "boss32_01 (tiles).psgcompr" -noremovedupes -nomirror -planar -tileoffset 0 -savepalette "boss32_01 (palette).bin" -fullpalette -spritepalette -exit
bmp2tile.exe raw\boss32_02.png -savetiles "boss32_02 (tiles).psgcompr" -noremovedupes -nomirror -planar -tileoffset 0 -savepalette "boss32_02 (palette).bin" -fullpalette -spritepalette -exit


REM boss64
bmp2tile.exe raw\boss64_00.png -savetiles "boss64_00 (tiles).psgcompr" -noremovedupes -nomirror -planar -tileoffset 0 -savepalette "boss64_00 (palette).bin" -fullpalette -spritepalette -exit
bmp2tile.exe raw\boss64_01.png -savetiles "boss64_01 (tiles).psgcompr" -noremovedupes -nomirror -planar -tileoffset 0 -savepalette "boss64_01 (palette).bin" -fullpalette -spritepalette -exit
bmp2tile.exe raw\boss64_02.png -savetiles "boss64_02 (tiles).psgcompr" -noremovedupes -nomirror -planar -tileoffset 0 -savepalette "boss64_02 (palette).bin" -fullpalette -spritepalette -exit
bmp2tile.exe raw\boss64_03.png -savetiles "boss64_03 (tiles).psgcompr" -noremovedupes -nomirror -planar -tileoffset 0 -savepalette "boss64_03 (palette).bin" -fullpalette -spritepalette -exit
bmp2tile.exe raw\boss64_04.png -savetiles "boss64_04 (tiles).psgcompr" -noremovedupes -nomirror -planar -tileoffset 0 -savepalette "boss64_04 (palette).bin" -fullpalette -spritepalette -exit
bmp2tile.exe raw\boss64_05.png -savetiles "boss64_05 (tiles).psgcompr" -noremovedupes -nomirror -planar -tileoffset 0 -savepalette "boss64_05 (palette).bin" -fullpalette -spritepalette -exit

cd ..
folder2c bank3 bank3 3
sdcc -c --no-std-crt0 -mz80 --Werror --opt-code-speed --constseg BANK3 bank3.c

del *.asm > nul; del *.lst > nul; del *.sym > nul

cd ..
cd scripts