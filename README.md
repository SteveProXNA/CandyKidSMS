# Candy Kid
Candy Kid game for the SMS Power! 2020 Competition.

###### RELEASE
Friday, 27th March 2020

###### INTRO
Candy Kid is a simple maze chase game.  Eat all the candy to pass each level.  Eat all bonuses to maximize your score!
<br />
The 3x Candy "Mama" enemies Pro / Adi / Suz have different personalities and alternate between scatter and attack.
<br />
Blast your way through 100x levels of crazy maze paced action!  Simple. Addictive. Fun.

###### HISTORY
Candy Kid video game was originally programmed by Grandstand Leisure from New Zealand in September 1984.
<br />
The game written in BASIC on the Sega SC-3000.  Thanks to SMS Power! original source code can be found [here](https://www.smspower.org/Scans/SegaComputer-Magazine-Issue02?gallerypage=17).
<br />
<br />
Candy Kid was re-written in C#/.NET and XNA for Windows PC and ported to iOS / Android using MonoGame.
<br />
Now, thanks to the awesome community at SMS Power! Candy Kid is available for the Sega Master System.

###### TOOLS
- Programming:	devkitSMS
- Compiler		sdcc 3.6
- Languages:	C / Z80
- Visual Studio 2015
- Graphics:		BMP2Tile 0.43 / GIMP2 / paint.net
- Music:		Mod2Psg2 / VGM2PSG
- Assembler:	WLA-DX
- Emulators:	Emulicious / Fusion / Meka

###### SOURCE CODE
http://github.com/SteveProXNA/CandyKidSMS

###### ROM HACKING
You can hack this ROM!  
Download and dump CandyKid.sms into Hex Editor, e.g. HxD, and modify the bytes:
- 0x004F	Debugger	Used to show debugging info for game.
- 0x0050	Invincible	Non-zero value enables invincibility.
- 0x0051	FullBoost	Non-zero value enables maximum boost.
- 0x0052	Trees Type	Set value to 1=Show otherwise 2=Kill.
- 0x0053	Exits Type	Set value to 1=Open otherwise 2=Shut.
- 0x0054	Difficulty	Set value to 1=Easy otherwise 2=Hard.
- 0x0055	Game Speed	Set value to 1=Slow otherwise 2=Fast.
- 0x0056	World No.	Set start World no currently 1 to 10.
- 0x0057	Round No.	Set start Round no currently 1 to 10.
- 0x0058	Music Off	Set 0=Music to play otherwise silent.
- 0x0059	Sound Off	Set 0=Sound to play otherwise silent.

###### BONUSES
There are 4x different bonuses: 100 / 200 / 400 / 800 pts.  Double bonus points after level 70.
<br />
Player will receive extra 2000 pts after eating all candy and collecting all bonuses in level.

###### CHEATS
Press button 2 five times on Title screen and you'll be invincible each game this is actioned.
<br />
Press and hold button 2 during game play to action Game Over and force quit out of game.
<br />
Press and hold button 2 on Splash screen to reset High score and all options previously saved.

###### CREDITS
Extra special thanks to: sverx for [devkitSMS](https://github.com/sverx/devkitSMS) and Calindro for their 24/7 Tech Support!
<br />
Plus shout out to [eruiz00](http://www.smspower.org/forums/member10267) as I used many programming tricks from "Astro Force"
<br />
Also, I used a lot of programming tricks from [haroldoop](http://www.smspower.org/forums/member601)'s various code samples.
<br />
Finally, thanks goes to: Maxim, Martin, Ville Helin, Steve Snake, Bock + Kusfo

###### INVOLVEMENT
Currently, there are 100x levels but game has twice capacity - please let me know if you'd like to design some levels :)
<br />
Feel free to give your input: should Candy Mamas scatter and/or attack for different duration, different speeds etc.?

###### SOCIAL MEDIA
- Facebook https://www.facebook.com/CandyKidVideoGame
- Blogger  http://steveproxna.blogspot.com/search/label/Candy%20Kid

###### DOCUMENTATION
Links to documentation on games written for the Sega Master System using devkitSMS:
http://steveproxna.blogspot.com/2017/09/devkitsms-programming-setup.html
<br />
http://steveproxna.blogspot.com/2017/11/devkitsms-programming-sample.html
<br />
http://steveproxna.blogspot.com/2018/03/devkitsms-programming-sample-ii.html
<br />
http://steveproxna.blogspot.com/2019/04/devkitsms-programming-sample-iii.html

###### COMPANY BIO
StevePro Studios is an independent game developer that builds and publishes 80s retro arcade video games!
<br />
Founded by Steven Boland "SteveProXNA" (Jan-2007) a "one man team of one" currently based in Dublin, Ireland.
<br />
<br />
Original Candy Kid builds are available here:
<br />
- iOS		http://apple.co/1QcidUk
- Android	http://goo.gl/5rWsYO
- PC		http://amzn.to/1QiHM9d

###### CONTACT
- Blog:		http://steveproxna.blogspot.com
- Email:	steven_boland@hotmail.com
- Twitter:	[@SteveProXNA](http://twitter.com/SteveProXNA)
