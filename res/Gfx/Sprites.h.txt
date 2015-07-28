#ifndef _SPRITES_H_
#define _SPRITES_H_

extern const SpriteDefinition SPR_Eagle;
extern const SpriteDefinition SPR_Arrow;
extern const SpriteDefinition SPR_Pwr;
extern const SpriteDefinition SPR_ObjsN;
extern const SpriteDefinition SPR_ObjsB;

//Sprite IDs for Powerups
#define Pwr_MPuck 0
#define Pwr_BStick 1
#define Pwr_Bumper 2
#define Pwr_Block 3
#define Pwr_Slow 4
#define Pwr_Kill 5
#define Pwr_Swap 6
#define Pwr_Fast 7
#define Pwr_Invis 8
#define Pwr_BSaver 9
#define SPR_Puck 10
#define Pwr_Null 11

//Sprite IDs for ObjsN
#define ON_Red 0
#define ON_Blue 1
#define ON_Bumper 2
#define ON_WTop 3
#define ON_WMid 4
#define ON_WBot 5
#define ON_Invis 6
#define ON_Null 7

//Sprite IDs for ObjsB
#define OB_Red 0
#define OB_Blue 1

/*
typedef struct
{
    *Sprite hand;     //image handle
    u8 w;            //Image width
    u8 h;            //Image height
    u16 x1;         //x coord of top left corner
    u16 y1;         //y coord of top left corner
    u16 x2;         //x coord of bottom right corner
    u16 y2;         //y coord of bottom right corner
    //u8 V;     //Resultant velocity
} Box;
*/
#endif // _SPRITES_H_
