REM bank11
@echo off

cd ..
cd banks
cd bank11

REM boss32
bmp2tile.exe raw\boss32_00.png -savetiles "boss32_00 (tiles).psgcompr" -noremovedupes -nomirror -planar -tileoffset 0 -savepalette "boss32_00 (palette).bin" -fullpalette -spritepalette -exit
bmp2tile.exe raw\boss32_01.png -savetiles "boss32_01 (tiles).psgcompr" -noremovedupes -nomirror -planar -tileoffset 0 -savepalette "boss32_01 (palette).bin" -fullpalette -spritepalette -exit
bmp2tile.exe raw\boss32_02.png -savetiles "boss32_02 (tiles).psgcompr" -noremovedupes -nomirror -planar -tileoffset 0 -savepalette "boss32_02 (palette).bin" -fullpalette -spritepalette -exit

cd ..
folder2c bank11 bank11 11

sdcc -c --no-std-crt0 -mz80 --Werror --opt-code-speed --constseg BANK11 bank11.c

del *.asm > nul; del *.lst > nul; del *.sym > nul

cd ..
cd scripts