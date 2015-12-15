//Contains sprite-related def/functions
#include "../inc/SpriteManip.h"

_Box GetBox(Sprite* spr)
{
    _Box outbox;
    outbox.hand=&spr;
    outbox.w=spr->frame->w;
    outbox.h=spr->frame->h;
    outbox.x1=spr->x;
    outbox.y1=spr->y;
    outbox.x2=(spr->x)+(outbox.w);
    outbox.y2=(spr->y)+(outbox.h);
    outbox.cx=(outbox.x1)+(outbox.w>>1);    //Divide by 2
    outbox.cy=(outbox.y1)+(outbox.h>>1);
    return outbox;
}
