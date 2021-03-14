#include "bank4.h"
#include "bank5.h"
#include "bank6.h"
#include "bank7.h"
#include "bank8.h"
#include "bank9.h"
#include "bank10.h"
#include "bank11.h"
#include "bank12.h"
#include "bank13.h"


// FIXED bank.
// Audio Manager.
const unsigned char *music_object_data[] =
{
	mus_level_psg,
	mus_cont_psg,
	mus_over_psg,
	mus_game01_psg,
	mus_game02_psg,
	mus_game03_psg,
	mus_beat_psg,
	mus_candykid_psg,
	mus_boss01_psg,
	mus_boss02_psg,
	mus_boss03_psg,
};
const unsigned char music_object_bank[] =
{
	mus_level_psg_bank,
	mus_cont_psg_bank,
	mus_over_psg_bank,
	mus_game01_psg_bank,
	mus_game02_psg_bank,
	mus_game03_psg_bank,
	mus_beat_psg_bank,
	mus_candykid_psg_bank,
	mus_boss01_psg_bank,
	mus_boss02_psg_bank,
	mus_boss03_psg_bank,
};


// FIXED bank.
// Boss Manager.
const unsigned char *boss_object_tiles[] =
{
	boss32_00__tiles__psgcompr,
	boss32_01__tiles__psgcompr,
	boss32_02__tiles__psgcompr,
	boss64_00__tiles__psgcompr,
	boss64_01__tiles__psgcompr,
	boss64_02__tiles__psgcompr,
	boss64_03__tiles__psgcompr,
	boss64_04__tiles__psgcompr,
	boss64_05__tiles__psgcompr,
};

const unsigned char *boss_object_color[] =
{
	boss32_00__palette__bin,
	boss32_01__palette__bin,
	boss32_02__palette__bin,
	boss64_00__palette__bin,
	boss64_01__palette__bin,
	boss64_02__palette__bin,
	boss64_03__palette__bin,
	boss64_04__palette__bin,
	boss64_05__palette__bin,
};

const unsigned char boss_object_bank[] =
{
	boss32_00__tiles__psgcompr_bank,
	boss32_01__tiles__psgcompr_bank,
	boss32_02__tiles__psgcompr_bank,
	boss64_00__tiles__psgcompr_bank,
	boss64_01__tiles__psgcompr_bank,
	boss64_02__tiles__psgcompr_bank,
	boss64_03__tiles__psgcompr_bank,
	boss64_04__tiles__psgcompr_bank,
	boss64_05__tiles__psgcompr_bank,
};

const unsigned char boss_object_speed[] =
{
//Pro: ES,EF,HS,HF.
		1, 1, 2, 1, 		// Boss1
		1, 1, 3, 3, 		// Boss2
//Adi: ES,EF,HS,HF.
		1, 1, 1, 1, 		// Boss1
		2, 2, 3, 3, 		// Boss2
//Suz: ES,EF,HS,HF.
		1, 1, 1, 1, 		// Boss1
		1, 1, 2, 2, 		// Boss2
};
const unsigned char boss_object_delay[] =
{
//Pro: ES,EF,HS,HF.
		2, 2, 3, 1, 		// Boss1
		1, 1, 2, 2, 		// Boss2
//Adi: ES,EF,HS,HF.
		3, 3, 2, 2, 		// Boss1
		3, 3, 3, 3, 		// Boss2
//Suz: ES,EF,HS,HF.
		4, 4, 3, 3, 		// Boss1
		2, 2, 3, 3, 		// Boss2
};


// FIXED bank.
// Enemy Manager
const unsigned char enemy_object_image[] =
{
	0, 2, 4, 12,		// Pro images.
	14, 16, 24, 26,		// Adi images.
	28, 36, 38, 40,		// Suz images.
};

const unsigned char enemy_object_speed[] =
{
//Pro: ES,EF,HS,HF.
	2, 3, 1, 3, 		// Normal
	2, 1, 3, 2, 		// Boost!
//Adi: ES,EF,HS,HF.
	1, 1, 2, 3, 		// Normal
	1, 2, 3, 1, 		// Boost!
//Suz: ES,EF,HS,HF.
	1, 1, 1, 2, 		// Normal
	1, 1, 2, 3, 		// Boost!
};
const unsigned char enemy_object_delay[] =
{
//Pro: ES,EF,HS,HF.
	3, 3, 1, 2, 		// Normal
	3, 1, 2, 1, 		// Boost!
//Adi: ES,EF,HS,HF.
	2, 2, 3, 3, 		// Normal
	2, 3, 3, 1, 		// Boost!
//Suz: ES,EF,HS,HF.
	3, 3, 2, 3, 		// Normal
	3, 2, 3, 3, 		// Boost!
};


const unsigned char enemy_object_hands[] =
{
	//	ES, EF, HS, HF.
	90, 80, 70, 60,		// Pro
	95, 85, 75, 65,		// Adi
	99, 90, 80, 70,		// Suz
};

const unsigned char enemy_object_waits[] =
{
	//	ES, EF, HS, HF.
	80, 60, 40, 20,		// Pro
	85, 65, 45, 25,		// Adi
	90, 70, 50, 30,		// Suz
};
const unsigned char enemy_object_tours[] =
{
	//	ES, EF, HS, HF.
	64, 72, 80, 88,		// Pro
	68, 76, 84, 92,		// Adi
	72, 80, 88, 96,		// Suz
};
const unsigned char enemy_object_kills[] =
{
	//	ES, EF, HS, HF.
	65, 73, 81, 89,		// Pro
	69, 77, 85, 93,		// Adi
	73, 81, 89, 97,		// Suz
};


// FIXED bank.
// Gamer Manager.
const unsigned char gamer_object_image[] = { 0, 2, 4, 12, 14, 16 };
const unsigned char gamer_object_speed[] = { 1, 2, 3, 3 };
const unsigned char gamer_object_delay[] = { 1, 1, 2, 1 };


// FIXED bank.
// Locale Manager.
const unsigned char *locale_object_texts[] =
{
	"V3.0",
	"INSERT COIN(S)",
	"CHEAT!",
	" HIGH",
	"SCORE",
	"LIVES",
	"LEVEL",
	"BOOST",
	"EASY",
	"HARD",
	"SLOW",
	"FAST",
	"WORLD",
	"ROUND",
	"LEVEL IS",
	"COMPLETE",
	"PERFECT!",
	"CONTINUE",
	" YES  NO",
	"  GAME  ",
	"  OVER  ",
	"CANDYKID",
	"  WINS  ",
	"(C)1984",
	"MODE",
	"ENEMY",		// 25
	"PRO ",
	"ADI ",
	"SUZ ",
	"CANDY",		// 29
	"KID ",
	" PTS ",
	"NEW GAME",
	"CONTINUE",
	"OPTIONS",
	"KID1",
	"KID2",
	"PRO1",
	"PRO2",
	"ADI1",
	"ADI2",
	"SUZ1",
	"SUZ2",
	"TREES",
	"AVOID",
	"DEATH",
	"EXITS",
	" OPEN",
	" SHUT",
	"DIFFICULTY",
	"BIG BOSS",
	"LIL BOSS",
};


// FIXED bank.
// Level Manager.
const unsigned char *level_object_AAdata[] =
{
	level0101_txt,
	level0102_txt,
	level0103_txt,
	level0104_txt,
	level0105_txt,
	level0106_txt,
	level0107_txt,
	level0108_txt,
	level0109_txt,
	level0110_txt,
	level0201_txt,
	level0202_txt,
	level0203_txt,
	level0204_txt,
	level0205_txt,
	level0206_txt,
	level0207_txt,
	level0208_txt,
	level0209_txt,
	level0210_txt,
	level0301_txt,
	level0302_txt,
	level0303_txt,
	level0304_txt,
	level0305_txt,
	level0306_txt,
	level0307_txt,
	level0308_txt,
	level0309_txt,
	level0310_txt,
	level0401_txt,
	level0402_txt,
	level0403_txt,
	level0404_txt,
	level0405_txt,
	level0406_txt,
	level0407_txt,
	level0408_txt,
	level0409_txt,
	level0410_txt,
	level0501_txt,
	level0502_txt,
	level0503_txt,
	level0504_txt,
	level0505_txt,
	level0506_txt,
	level0507_txt,
	level0508_txt,
	level0509_txt,
	level0510_txt,
	level0601_txt,
	level0602_txt,
	level0603_txt,
	level0604_txt,
	level0605_txt,
	level0606_txt,
	level0607_txt,
	level0608_txt,
	level0609_txt,
	level0610_txt,
	level0701_txt,
	level0702_txt,
	level0703_txt,
	level0704_txt,
	level0705_txt,
	level0706_txt,
	level0707_txt,
	level0708_txt,
	level0709_txt,
	level0710_txt,
	level0801_txt,
	level0802_txt,
	level0803_txt,
	level0804_txt,
	level0805_txt,
	level0806_txt,
	level0807_txt,
	level0808_txt,
	level0809_txt,
	level0810_txt,
	level0901_txt,
	level0902_txt,
	level0903_txt,
	level0904_txt,
	level0905_txt,
	level0906_txt,
	level0907_txt,
	level0908_txt,
	level0909_txt,
	level0910_txt,
	level1001_txt,
	level1002_txt,
	level1003_txt,
	level1004_txt,
	level1005_txt,
	level1006_txt,
	level1007_txt,
	level1008_txt,
	level1009_txt,
	level1010_txt,
};

const unsigned char level_object_AAsize[] =
{
	level0101_txt_size,
	level0102_txt_size,
	level0103_txt_size,
	level0104_txt_size,
	level0105_txt_size,
	level0106_txt_size,
	level0107_txt_size,
	level0108_txt_size,
	level0109_txt_size,
	level0110_txt_size,
	level0201_txt_size,
	level0202_txt_size,
	level0203_txt_size,
	level0204_txt_size,
	level0205_txt_size,
	level0206_txt_size,
	level0207_txt_size,
	level0208_txt_size,
	level0209_txt_size,
	level0210_txt_size,
	level0301_txt_size,
	level0302_txt_size,
	level0303_txt_size,
	level0304_txt_size,
	level0305_txt_size,
	level0306_txt_size,
	level0307_txt_size,
	level0308_txt_size,
	level0309_txt_size,
	level0310_txt_size,
	level0401_txt_size,
	level0402_txt_size,
	level0403_txt_size,
	level0404_txt_size,
	level0405_txt_size,
	level0406_txt_size,
	level0407_txt_size,
	level0408_txt_size,
	level0409_txt_size,
	level0410_txt_size,
	level0501_txt_size,
	level0502_txt_size,
	level0503_txt_size,
	level0504_txt_size,
	level0505_txt_size,
	level0506_txt_size,
	level0507_txt_size,
	level0508_txt_size,
	level0509_txt_size,
	level0510_txt_size,
	level0601_txt_size,
	level0602_txt_size,
	level0603_txt_size,
	level0604_txt_size,
	level0605_txt_size,
	level0606_txt_size,
	level0607_txt_size,
	level0608_txt_size,
	level0609_txt_size,
	level0610_txt_size,
	level0701_txt_size,
	level0702_txt_size,
	level0703_txt_size,
	level0704_txt_size,
	level0705_txt_size,
	level0706_txt_size,
	level0707_txt_size,
	level0708_txt_size,
	level0709_txt_size,
	level0710_txt_size,
	level0801_txt_size,
	level0802_txt_size,
	level0803_txt_size,
	level0804_txt_size,
	level0805_txt_size,
	level0806_txt_size,
	level0807_txt_size,
	level0808_txt_size,
	level0809_txt_size,
	level0810_txt_size,
	level0901_txt_size,
	level0902_txt_size,
	level0903_txt_size,
	level0904_txt_size,
	level0905_txt_size,
	level0906_txt_size,
	level0907_txt_size,
	level0909_txt_size,
	level0909_txt_size,
	level0910_txt_size,
	level1001_txt_size,
	level1002_txt_size,
	level1003_txt_size,
	level1004_txt_size,
	level1005_txt_size,
	level1006_txt_size,
	level1007_txt_size,
	level1010_txt_size,
	level1010_txt_size,
	level1010_txt_size,
};

const unsigned char level_object_AAbank[] =
{
	level0101_txt_bank,
	level0102_txt_bank,
	level0103_txt_bank,
	level0104_txt_bank,
	level0105_txt_bank,
	level0106_txt_bank,
	level0107_txt_bank,
	level0108_txt_bank,
	level0109_txt_bank,
	level0110_txt_bank,
	level0201_txt_bank,
	level0202_txt_bank,
	level0203_txt_bank,
	level0204_txt_bank,
	level0205_txt_bank,
	level0206_txt_bank,
	level0207_txt_bank,
	level0208_txt_bank,
	level0209_txt_bank,
	level0210_txt_bank,
	level0301_txt_bank,
	level0302_txt_bank,
	level0303_txt_bank,
	level0304_txt_bank,
	level0305_txt_bank,
	level0306_txt_bank,
	level0307_txt_bank,
	level0308_txt_bank,
	level0309_txt_bank,
	level0310_txt_bank,
	level0401_txt_bank,
	level0402_txt_bank,
	level0403_txt_bank,
	level0404_txt_bank,
	level0405_txt_bank,
	level0406_txt_bank,
	level0407_txt_bank,
	level0408_txt_bank,
	level0409_txt_bank,
	level0410_txt_bank,
	level0501_txt_bank,
	level0502_txt_bank,
	level0503_txt_bank,
	level0504_txt_bank,
	level0505_txt_bank,
	level0506_txt_bank,
	level0507_txt_bank,
	level0508_txt_bank,
	level0509_txt_bank,
	level0510_txt_bank,
	level0601_txt_bank,
	level0602_txt_bank,
	level0603_txt_bank,
	level0604_txt_bank,
	level0605_txt_bank,
	level0606_txt_bank,
	level0607_txt_bank,
	level0608_txt_bank,
	level0609_txt_bank,
	level0610_txt_bank,
	level0701_txt_bank,
	level0702_txt_bank,
	level0703_txt_bank,
	level0704_txt_bank,
	level0705_txt_bank,
	level0706_txt_bank,
	level0707_txt_bank,
	level0708_txt_bank,
	level0709_txt_bank,
	level0710_txt_bank,
	level0801_txt_bank,
	level0802_txt_bank,
	level0803_txt_bank,
	level0804_txt_bank,
	level0805_txt_bank,
	level0806_txt_bank,
	level0807_txt_bank,
	level0808_txt_bank,
	level0809_txt_bank,
	level0810_txt_bank,
	level0901_txt_bank,
	level0902_txt_bank,
	level0903_txt_bank,
	level0904_txt_bank,
	level0905_txt_bank,
	level0906_txt_bank,
	level0907_txt_bank,
	level0909_txt_bank,
	level0909_txt_bank,
	level0910_txt_bank,
	level1001_txt_bank,
	level1002_txt_bank,
	level1003_txt_bank,
	level1004_txt_bank,
	level1005_txt_bank,
	level1006_txt_bank,
	level1007_txt_bank,
	level1010_txt_bank,
	level1010_txt_bank,
	level1010_txt_bank,
};

extern const unsigned char *level_object_BBdata[] =
{
	level1101_txt,
	level1102_txt,
	level1103_txt,
	level1104_txt,
	level1105_txt,
	level1106_txt,
	level1107_txt,
	level1108_txt,
	level1109_txt,
	level1110_txt,
	level1201_txt,
	level1202_txt,
	level1203_txt,
	level1204_txt,
	level1205_txt,
	level1206_txt,
	level1207_txt,
	level1208_txt,
	level1209_txt,
	level1210_txt,
	level1301_txt,
	level1302_txt,
	level1303_txt,
	level1304_txt,
	level1305_txt,
	level1306_txt,
	level1307_txt,
	level1308_txt,
	level1309_txt,
	level1310_txt,
	level1401_txt,
	level1402_txt,
	level1403_txt,
	level1404_txt,
	level1405_txt,
	level1406_txt,
	level1407_txt,
	level1408_txt,
	level1409_txt,
	level1410_txt,
	level1501_txt,
	level1502_txt,
	level1503_txt,
	level1504_txt,
	level1505_txt,
	level1506_txt,
	level1507_txt,
	level1508_txt,
	level1509_txt,
	level1510_txt,
	level1601_txt,
	level1602_txt,
	level1603_txt,
	level1604_txt,
	level1605_txt,
	level1606_txt,
	level1607_txt,
	level1608_txt,
	level1609_txt,
	level1610_txt,
	level1701_txt,
	level1702_txt,
	level1703_txt,
	level1704_txt,
	level1705_txt,
	level1706_txt,
	level1707_txt,
	level1708_txt,
	level1709_txt,
	level1710_txt,
	level1801_txt,
	level1802_txt,
	level1803_txt,
	level1804_txt,
	level1805_txt,
	level1806_txt,
	level1807_txt,
	level1808_txt,
	level1809_txt,
	level1810_txt,
	level1901_txt,
	level1902_txt,
	level1903_txt,
	level1904_txt,
	level1905_txt,
	level1906_txt,
	level1907_txt,
	level1908_txt,
	level1909_txt,
	level1910_txt,
	level2001_txt,
	level2002_txt,
	level2003_txt,
	level2004_txt,
	level2005_txt,
	level2006_txt,
	level2007_txt,
	level2008_txt,
	level2009_txt,
	level2010_txt,
};

extern const unsigned char level_object_BBsize[] =
{
	level1101_txt_size,
	level1102_txt_size,
	level1103_txt_size,
	level1104_txt_size,
	level1105_txt_size,
	level1106_txt_size,
	level1107_txt_size,
	level1108_txt_size,
	level1109_txt_size,
	level1110_txt_size,
	level1201_txt_size,
	level1202_txt_size,
	level1203_txt_size,
	level1204_txt_size,
	level1205_txt_size,
	level1206_txt_size,
	level1207_txt_size,
	level1208_txt_size,
	level1209_txt_size,
	level1210_txt_size,
	level1301_txt_size,
	level1302_txt_size,
	level1303_txt_size,
	level1304_txt_size,
	level1305_txt_size,
	level1306_txt_size,
	level1307_txt_size,
	level1308_txt_size,
	level1309_txt_size,
	level1310_txt_size,
	level1401_txt_size,
	level1402_txt_size,
	level1403_txt_size,
	level1404_txt_size,
	level1405_txt_size,
	level1406_txt_size,
	level1407_txt_size,
	level1408_txt_size,
	level1409_txt_size,
	level1410_txt_size,
	level1501_txt_size,
	level1502_txt_size,
	level1503_txt_size,
	level1504_txt_size,
	level1505_txt_size,
	level1506_txt_size,
	level1507_txt_size,
	level1508_txt_size,
	level1509_txt_size,
	level1510_txt_size,
	level1601_txt_size,
	level1602_txt_size,
	level1603_txt_size,
	level1604_txt_size,
	level1605_txt_size,
	level1606_txt_size,
	level1607_txt_size,
	level1608_txt_size,
	level1609_txt_size,
	level1610_txt_size,
	level1701_txt_size,
	level1702_txt_size,
	level1703_txt_size,
	level1704_txt_size,
	level1705_txt_size,
	level1706_txt_size,
	level1707_txt_size,
	level1708_txt_size,
	level1709_txt_size,
	level1710_txt_size,
	level1801_txt_size,
	level1802_txt_size,
	level1803_txt_size,
	level1804_txt_size,
	level1805_txt_size,
	level1806_txt_size,
	level1807_txt_size,
	level1808_txt_size,
	level1809_txt_size,
	level1810_txt_size,
	level1901_txt_size,
	level1902_txt_size,
	level1903_txt_size,
	level1904_txt_size,
	level1905_txt_size,
	level1906_txt_size,
	level1907_txt_size,
	level1908_txt_size,
	level1909_txt_size,
	level1910_txt_size,
	level2001_txt_size,
	level2002_txt_size,
	level2003_txt_size,
	level2004_txt_size,
	level2005_txt_size,
	level2006_txt_size,
	level2007_txt_size,
	level2008_txt_size,
	level2009_txt_size,
	level2010_txt_size,
};

extern const unsigned char level_object_BBbank[] =
{
	level1101_txt_bank,
	level1102_txt_bank,
	level1103_txt_bank,
	level1104_txt_bank,
	level1105_txt_bank,
	level1106_txt_bank,
	level1107_txt_bank,
	level1108_txt_bank,
	level1109_txt_bank,
	level1110_txt_bank,
	level1201_txt_bank,
	level1202_txt_bank,
	level1203_txt_bank,
	level1204_txt_bank,
	level1205_txt_bank,
	level1206_txt_bank,
	level1207_txt_bank,
	level1208_txt_bank,
	level1209_txt_bank,
	level1210_txt_bank,
	level1301_txt_bank,
	level1302_txt_bank,
	level1303_txt_bank,
	level1304_txt_bank,
	level1305_txt_bank,
	level1306_txt_bank,
	level1307_txt_bank,
	level1308_txt_bank,
	level1309_txt_bank,
	level1310_txt_bank,
	level1401_txt_bank,
	level1402_txt_bank,
	level1403_txt_bank,
	level1404_txt_bank,
	level1405_txt_bank,
	level1406_txt_bank,
	level1407_txt_bank,
	level1408_txt_bank,
	level1409_txt_bank,
	level1410_txt_bank,
	level1501_txt_bank,
	level1502_txt_bank,
	level1503_txt_bank,
	level1504_txt_bank,
	level1505_txt_bank,
	level1506_txt_bank,
	level1507_txt_bank,
	level1508_txt_bank,
	level1509_txt_bank,
	level1510_txt_bank,
	level1601_txt_bank,
	level1602_txt_bank,
	level1603_txt_bank,
	level1604_txt_bank,
	level1605_txt_bank,
	level1606_txt_bank,
	level1607_txt_bank,
	level1608_txt_bank,
	level1609_txt_bank,
	level1610_txt_bank,
	level1701_txt_bank,
	level1702_txt_bank,
	level1703_txt_bank,
	level1704_txt_bank,
	level1705_txt_bank,
	level1706_txt_bank,
	level1707_txt_bank,
	level1708_txt_bank,
	level1709_txt_bank,
	level1710_txt_bank,
	level1801_txt_bank,
	level1802_txt_bank,
	level1803_txt_bank,
	level1804_txt_bank,
	level1805_txt_bank,
	level1806_txt_bank,
	level1807_txt_bank,
	level1808_txt_bank,
	level1809_txt_bank,
	level1810_txt_bank,
	level1901_txt_bank,
	level1902_txt_bank,
	level1903_txt_bank,
	level1904_txt_bank,
	level1905_txt_bank,
	level1906_txt_bank,
	level1907_txt_bank,
	level1908_txt_bank,
	level1909_txt_bank,
	level1910_txt_bank,
	level2001_txt_bank,
	level2002_txt_bank,
	level2003_txt_bank,
	level2004_txt_bank,
	level2005_txt_bank,
	level2006_txt_bank,
	level2007_txt_bank,
	level2008_txt_bank,
	level2009_txt_bank,
	level2010_txt_bank,
};



//void engine_option_manager_clear()
//{
//	//unsigned char x[ NUM_DIRECTIONS ] = { 2, 14, 2, 14 };
//	//unsigned char y[ NUM_DIRECTIONS ] = { 0, 0, 1, 1 };
//	//unsigned char idx;
//	//for( idx = 0; idx < NUM_DIRECTIONS; idx++ )
//	//{
//	//	engine_font_manager_draw_text( locale_object_blank14, SCREEN_TILE_LEFT + x[ idx ], TEXT4_Y + y[ idx ] );
//	//}
//	engine_font_manager_draw_text( locale_object_blank14, SCREEN_TILE_LEFT + 2, TEXT4_Y + 0 );
//	engine_font_manager_draw_text( locale_object_blank14, SCREEN_TILE_LEFT + 14, TEXT4_Y + 0 );
//	engine_font_manager_draw_text( locale_object_blank14, SCREEN_TILE_LEFT + 2, TEXT4_Y + 1 );
//	engine_font_manager_draw_text( locale_object_blank14, SCREEN_TILE_LEFT + 14, TEXT4_Y + 1 );
//}