//Contains sprite-related def/functions
#include "../inc/SpriteManip.h"
#include "../inc/main.h"

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

//IMPORTANT routine to do different collision types
void StdCol(_Box *Pt, u8 T, s8 S, u8 *SI)
{
    //Pt()=Collision box array, passed by ref
    //Pt(1).STUFF= Colider
    //Pt(2).STUFF= Colided object

    //T~%%=Type=
    //0=Solid collision
    //1=(DELETED)
    //2=complex rebound (sticks hitting pucks, vtr math)
    // S%%= Index of Puck
    //3=Death collision (pucks hitting powerups, powerups "disappear")
    // S%%= item to object to kill
    //  If abs(S%%)=-1=kill motion
    //  If abs(S%%)=-1=maintain motion

    //SI%%=Sound effect to play. If=0, don't play one

    const u8 PCENT=50;  //Speed adjustment factor for slomo/fastmo powerups
    Vect2D_s16 NewVtr;
    switch(T)
    {
        //Complex rebound (paddle vs. puck)
        case 2:
            NewVtr.x=Pt[1].cx-Pt[0].cx;
            NewVtr.y=Pt[1].cy-Pt[0].cy;

            //Slomo and fastmo speed adjustments]
            if ((Player[0].aPwr==Pwr_Slow)||(Player[1].aPwr==Pwr_Slow))
            {
                NewVtr.x=PCentChng(NewVtr.x,PCENT,NTRUE);
                NewVtr.y=PCentChng(NewVtr.y,PCENT,NTRUE);
            }
            if ((Player[0].aPwr==Pwr_Fast)||(Player[1].aPwr==Pwr_Fast))
            {
                NewVtr.x=PCentChng(NewVtr.x,PCENT,PTRUE);
                NewVtr.y=PCentChng(NewVtr.y,PCENT,PTRUE);
            }

            //Apply new vector to other obj (the puck)
            NewVtr.x=NewVtr.x/4;
            NewVtr.y=NewVtr.y/4;
            Pux[S].v=NewVtr;
            break;


        //Death collision (sunk multi-pucks, puck vs. powerups with powerups dying)
        case 3:
            // !@ Insert code here
            break;


        //Solid collision.
        default:
            //Utilises clipping in order to make the colider near edge
            //of the collided object if overlapped

            //If colider hit collided object from left
            /*
            if ((Pt[0].x2>=Pt[1].x1)&&(Pt[0].x2<=Pt[1].x2))
            {
                NewVtr.x=Pt[1].x1-Pt[0].w;
                NewVtr.y=Pt[0].cy-2;
                NewVtr.x-=SPR_Origin;
                NewVtr.y-=SPR_Origin;
                SPR_setPosition(&(Pt[0].hand),NewVtr.x,NewVtr.y);
                Pt[0]=GetBox(&(Pt[0].hand));
            }
            */
            break;
    }

    if (SI!=SFX_31)
    {
        echo_play_sfx(SI); //Play sfx if applicable
    }
}

//Using collision boxes, return if two sprites have collided
u8 CheckCollision(_Box Pt[1])
{
    u8 collision=_FALSE;

    if ((Pt[0].x2>=Pt[1].x1)&&(Pt[0].x2<=Pt[1].x2))
    {
        if ((Pt[0].y1>=Pt[1].y1)&&(Pt[0].y1<=Pt[1].y2))
        {
            collision=PTRUE;
        }
        if ((Pt[0].y2>=Pt[1].y1)&&(Pt[0].y2<=Pt[1].y2))
        {
            collision=PTRUE;
        }
    }

    if ((Pt[0].x1>=Pt[1].x1)&&(Pt[0].x1<=Pt[1].x2))
    {
        if ((Pt[0].y1>=Pt[1].y1)&&(Pt[0].y1<=Pt[1].y2))
        {
            collision=PTRUE;
        }
        if ((Pt[0].y2>=Pt[1].y1)&&(Pt[0].y2<=Pt[1].y2))
        {
            collision=PTRUE;
        }
    }
    return collision;
}

//Function to return a percentage of a #
s16 PCentChng(s16 Valu, u8 PCent, s8 Delta)
{

    //Let
    //Valu~%%=Inputted value
    //PCent~%%=Percentage as int
    //Delta~%%=-1 or 1, for whether to add or subtract percent

    s16 outval;
    fix16 P;    //Percentage as decimal
    P=fix16Div(PCent,100);
    outval = fix16ToInt(intToFix16(Valu)+(intToFix16(Delta)*(intToFix16(P)*intToFix16(Valu))));
    return outval;
}
