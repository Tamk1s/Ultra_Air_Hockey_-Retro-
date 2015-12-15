#include <Genesis.h>
#include <sprite_eng.h>

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
    //u8 V;     //Resultant velocity
} _Box;

//Function protos
_Box GetBox(Sprite* spr);
