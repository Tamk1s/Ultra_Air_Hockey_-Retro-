#include <Genesis.h>
#include "../inc/main.h"
#include "../inc/DrawBG.h"
#include <joy.h>
#include <timer.h>
#include <vdp.h>
#include <vdp_pal.h>
#include <string.h>
#include "../res/Gfx/Sprites.h"
#include <sprite_eng.h>

//Global menu.c variables
//Menu stuff
u8 HItem=0;     //Hilighted menu Item
u8 SItem=0;     //Selected  menu Item
u8 MMin=0;      //Minimum ID value of menu
u8 MMax=2;      //Maximum ~
u8 Trig=_FALSE; //Generic bool trigger (usually for ending menus)

//Echo sound/bgm IDs (global because of joypad stuff :(
s32 S_ID=0;                                             //Sound ID
s32 S_Max=((sizeof(Sounds))/(sizeof(Sounds[0])))-1;     //Max amount of sounds
s32 M_ID=0;                                             //}
s32 M_Max=((sizeof(Songs))/(sizeof(Songs[0])))-1;       //}Ditto

//Function protos
void MainMenu();
void InitMenu(u8 h, u8 s, u8 a, u8 b, u8 ignore);
void BtnNada(u16 joy, u16 changed, u16 state);
void BtnHMenu(u16 joy, u16 changed, u16 state);
void ChrselMenu();
void OptionsMenu();
void BtnOptions(u16 joy, u16 changed, u16 state);
void Credits();
