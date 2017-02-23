//Contains Echo variables and global variable stuffs
#include <genesis.h>
#include "echo.h"
#include <maths.h>
#include "../res/Echo/data/Musres.h"
#include <string.h>
#include <vdp.h>
#include <sprite_eng.h>
#include "DrawBG.h"

//=============================
//Echo Stuff

//CUSTOM ECHO DRIVER CONSTANTS
//List of Echo instruments
static void* Instruments[] =
{
    //PCM Sound effects
    PCM_01,PCM_02,PCM_03,PCM_04,PCM_05,PCM_06,PCM_07,PCM_08,PCM_09,PCM_10,
    PCM_11,PCM_12,PCM_13,PCM_14,PCM_15,PCM_16,PCM_17,PCM_18,PCM_19,PCM_20,
    PCM_21,PCM_22,PCM_23,PCM_24,PCM_25,PCM_26,PCM_27,PCM_28,PCM_29,PCM_30,
    PCM_31,

    //Song 1/2, Hockey Fever (Intro/looped)
    FM_1_01,FM_1_02,FM_1_03,DAC_1_01,FM_1_04,DAC_1_02,DAC_1_03,DAC_1_04,DAC_1_05,DAC_1_06,
    DAC_1_07,DAC_1_08,DAC_1_09,FM_1_05,FM_1_06,DAC_1_10,DAC_1_11,

    //Song 3
    FM_3_01,FM_3_02,FM_3_03,FM_3_04,

    //Song 4
    DAC_4_01,DAC_4_02,DAC_4_03,FM_4_01,FM_4_02,FM_4_03,FM_4_04,FM_4_05,FM_4_06,FM_4_07,

    //Song 5
    FM_5_01,FM_5_02,FM_5_03,DAC_5_01,FM_5_04,DAC_5_02,DAC_5_03,FM_5_05,FM_5_06,DAC_5_04,
    DAC_5_05,FM_5_07,FM_5_08,DAC_5_06,FM_5_09,FM_5_10,

    //Song 6
    DAC_6_01,DAC_6_02,FM_6_01,FM_6_02,FM_6_03,FM_6_04,FM_6_05,FM_6_06,FM_6_07,FM_6_08,
    FM_6_09,FM_6_10,

    //Song 7
    DAC_7_01,DAC_7_02,DAC_7_03,FM_7_01,FM_7_02,FM_7_03,

    //Song 8
    DAC_8_01,DAC_8_02,DAC_8_03,DAC_8_04,FM_8_01,FM_8_02,FM_8_03,FM_8_04,

    //Song 9
    FM_9_01,FM_9_02,FM_9_03,FM_9_04,FM_9_05,FM_9_06,FM_9_07,

    //Song 10
    FM_10_01,FM_10_02,FM_10_03,

    //Song 11
    DAC_11_01,DAC_11_02,FM_11_01,DAC_11_03,DAC_11_04,DAC_11_05,FM_11_02,FM_11_03,FM_11_04,FM_11_05,

    //Song 12
    DAC_12_01,FM_12_01,FM_12_02,FM_12_03,FM_12_04,

    //Song 13
    DAC_13_01,DAC_13_02,DAC_13_03,FM_13_01,FM_13_02,FM_13_03,

    //Song 14
    DAC_14_01,DAC_14_02,DAC_14_03,FM_14_01,FM_14_02,FM_14_03,

    //Dummy/EagleSoft Ltd logo sfx
    PCM_31,PCM_32
};

//List of ESF Songs
static void* const Songs[] =
{
    BGM_01,BGM_02,BGM_03,BGM_04,BGM_05,BGM_06,BGM_07,BGM_08,BGM_09,BGM_10,
    BGM_11,BGM_12,BGM_13,BGM_14,
};

//List of ESF Song names
static char const Song_Names[][20] =
{
  "Hockey Fever (Intro)","Hockey Fever (Loop)","Nes mes2","Pit Title","Ice-Hockey '94 Theme",
  "Organmaster","Intro #101","Hurry Up!","Slowmotion","Castle Load","Complexity","Reflexity Music",
  "Chipmunk","Ice Hockey 2"
};

//@Fill me out!
//List of song lengths (MS)
//static u32 const Songs_Len[]=
//{
    //0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
//};

//List of ESF Sounds
static void* const Sounds[] =
{
    SFX_01,SFX_02,SFX_03,SFX_04,SFX_05,SFX_06,SFX_07,SFX_08,SFX_09,SFX_10,
    SFX_11,SFX_12,SFX_13,SFX_14,SFX_15,SFX_16,SFX_17,SFX_18,SFX_19,SFX_20,
    SFX_21,SFX_22,SFX_23,SFX_24,SFX_25,SFX_26,SFX_27,SFX_28,SFX_29,SFX_30,
    SFX_31,SFX_32,SFX_33
};

//List of ESF Sound names
static char const Sound_Names[][20] =
{
  "HiLite","Select","Hit","Deflect","Bumper","PwrGet","PwrUse",
  "Siren","vUAH","vPlay","vOptions","vCredits","vPlayers",
  "v1","v2","v3","v4","v5","v6","v7","v8","v9","v10","vTo","vBlue",
  "vRed","vGameover","vWins","vGoal","DeflectS","Buzzer","NULL","EagleSoft Ltd FMV"
};

/*
//@Contains lenght of sounds (in MS)
static u16 const Sounds_Len[] =
{
    333,500,500,150,367,1000,383,6334,1250,2134,
    1000,1000,2700,400,750,500,750,1000,50,400,
    400,500,384,750,500,1500,600,1000,1000,617,
    1684,0,1684 //Double check lens of this line
};
*/

/*
//@Contains length of songs (in MS)
static u32 const Songs_Len[]=
{

};
*/
//===========================

//global variables and constains
#define NTRUE -1    //Negative True
#define PTRUE 1     //Positive True
#define _FALSE 0    //False
#define DBUG 1      //Debug flag

//Options
static u8 Opts[]=
{
    PTRUE,_FALSE,_FALSE,PTRUE,PTRUE
};

u8 isPaused;    //Global to determine if game is paused

//Positions:
//[0] Players   1/2 Player mode
//[1] Diff      Difficulty. 1-3, EZ to Hard
//[2] Pwr       Powerups
//[3] music     Music
//[4] sfx       Sfx
//==============

//VDP Palette enums
//Following comments define their (general) use
 #define PLNPAL 0     //Palette line for plane images
 #define OBJPAL 1     //Palette line for Objects
 #define PWRPAL 2     //palette line for powerups
 #define MISCPAL 3    //palette line for misc stuff (?)

//VRAM constants
#define VDP_Width 320
#define VDP_Height 224
#define VDP_HWidth 160
#define VDP_HHeight 112
#define SPR_Origin 128

//Gameplay Variables

//Type for players
typedef struct
{
    u8 alive;               //If player is alive
    u8 sPwr;                //Saved powerup
    u8 aPwr;                //Active Powerup
    u8 Hitter;              //Who hit primary puck, for powerup collection. Only one player will have this as PTRUE~`
    u8 Score;               //Player's score
    u16 v;                  //resultant Velocity
    u8 c;                   //Counter for velocity multiplier (0-4)
    Vect2D_s16 ang;                 //@Angle to move stick
    u8 Side;                //Side of table for player. (_FALSE=Left, PTRUE=Right). Used for Swap place powerup/Center line division
} Plyr;

//Type for objects
typedef struct
{
    Sprite sprite[1];   //Sprite handle
    u8 Type;        //Main type. 0=null, 1=Bumper, 2=Ball Saver (DELETED), 3=Wall, 4=Powerups
    u8 Subtype;     //Sub type, for powerups. Powerups #1-10. #3 Ball Saver is deleted
} OB;

typedef struct
{
    Vect2D_s16 v;
    u8 active;
} Puck;

Vect2D_s16 V2D_s16_Zero;

//Object types and subtypes

//Types
#define OT_NULL 0
#define OT_Bumper 1
#define OT_Wall 2
#define OT_Pwr 3

//Subtypes
#define OST_NULL 0
#define OST_MPuck 1
#define OST_BStick 2
#define OST_Bumper 3
#define OST_Slow 4
#define OST_Kill 5
#define OST_Swap 6
#define OST_Fast 7
#define OST_Invis 8

//Use normal 2D Vectors?
/*
TYPE Vtr //Type for vectors
    v AS SINGLE //Velocity
    angle AS SINGLE //Angle (in degrees)
END TYPE
*/

//BOX datatype moved to Sprites.h/.c

#define Max_Pucks 3
#define Max_Objs 8

//Hardcoded offsets for sprite array allocation (stupid SPR_Update workaround)
#define SOff_paddle 0   //Always 0
#define SOff_pucks 2    //Always stars at 2
#define SOff_objects 5  //SOff_pucks+Max_Pucks
#define SOff_power 13   //SOff_objects+Max_Objs
#define SOff_spower 14  //Soff_Power+1
#define SOff_Total 15   //1-based total of sprites (for SPR_Update value)

Sprite GameSprites[SOff_Total];
Plyr Player[1];     //Players
OB Objs[Max_Objs];  //Array of objects
Puck Pux[Max_Pucks];//Pucks
//u8 ResetP;        //Flag to reset powerups's effects

//Game-specific Echo stuff
//u8 Song;      //Main song ID
//u8 PSong;     //Current powerup song ID

//main.h protos:
int main();
void BtnStick(u16 joy, u16 changed, u16 state);
void BtnStickMove(u8 numjoy, u16 value);
void StickStats(u8 ID, u8 dx, u8 dy,s8 nx, s8 ny);
void StickCollide(u8 ID);
void PuckMove(u8 act, Puck pux, Vect2D_s16 Ang);
void PuckCollide();
void GoalSink();
