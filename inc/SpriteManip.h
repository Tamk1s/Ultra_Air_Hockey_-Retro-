#include <Genesis.h>
#include <sprite_eng.h>
#include <maths.h>
#include "../res/Gfx/Sprites.h"

typedef struct
{
    Sprite* hand;    //image handle
    u8 w;           //Image width
    u8 h;           //Image height
    u16 cx;         //Center x value
    u16 cy;         //Center y value
    u16 x1;         //x coord of top left corner
    u16 y1;         //y coord of top left corner
    u16 x2;         //x coord of bottom right corner
    u16 y2;         //y coord of bottom right corner
    //Vect2D_s16 V;   //Resultant velocity
} _Box;

//Function protos
_Box GetBox(Sprite* spr);
void StdCol(_Box *Pt, u8 T, s8 S, u8 *SI);
u8 CheckCollision(_Box Pt[1]);
s16 PCentChng(s16 Valu, u8 PCent, s8 Delta);
