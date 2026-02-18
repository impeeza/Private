
Brewtendo Network (3DS Homebrew)

Publisher: AllisterMKW

This is a cosmetic Nintendo 3DS homebrew app inspired by Nimbus.
No networking or server switching occurs.

Build Instructions:
1. Install devkitARM + libctru
2. Place icon.png (48x48) and banner.png in gfx/
3. Run:
   make
4. Convert to CIA:
   makerom -f cia -o Brewtendo.cia -elf brewtendo.elf -rsf template.rsf -icon icon.smdh -banner banner.bnr
