#include <genesis.h>
#include "../inc/main.h"
//@#include "../res/Gfx/Planes.h"
#include "../inc/game.h"
#include <joy.h>

//MAIN GAME FUNCTION!
int main ( void )
{
        // Mainloop
        echo_init(Instruments);        // Load Instruments
        echo_set_pcm_rate(4);          // Set Echo PCM Rate of 10250Hz

        while(1)
        {
            JOY_init();                     // Init the joypad
            FMV();                          // Run EagleSoft Ltd FMV
            Title();                        // Run Title FMV
            MainMenu();                     // Run Main menu

            //MAIN GAME LOOP
            InitGame(PTRUE);
            JOY_setEventHandler( &BtnStickMove);    //Setup skip joy handler
            while(1)
            {
                if (DBUG==PTRUE)
                {
                    HUD();
                }
                VDP_waitVSync();                        //Sync
            }
        }
}

void BtnStickMove(u16 joy, u16 changed, u16 state)
{
    u8 Set=0;
    u8 ID=0;

    u8 dx=0;
    u8 dy=0;
    s8 nx=_FALSE;
    s8 ny=_FALSE;
    s16 x=0;
    s16 y=0;

    char val[2];
    u8 MoveIt=_FALSE;
    u8 Speeds[2][3]=
    {
        {0,1,2,3},
        {0,2,4,6},
        {0,3,6,9}
    };

    //Get speed set
    if ((Player[0].aPwr==Pwr_Slow) || (Player[1].aPwr==Pwr_Slow))
    {
        Set=0;
    }
    else if ((Player[0].aPwr==Pwr_Fast) || (Player[1].aPwr==Pwr_Fast))
    {
        Set=2;
    }
    else
    {
        Set=1;
    }


    if (joy==JOY_1)
    {
        ID=0;
    }
    else
    {
        ID=1;
    }

    //If player is alive
    if (Player[ID].alive==PTRUE)
    {
        //Up
        if (state & BUTTON_UP)
        {
            dy=Player[ID].v;
            ny=NTRUE;
            MoveIt=PTRUE;
        }
        else if (changed & BUTTON_UP)
        {
            dy=0;
            dy=_FALSE;

            MoveIt=_FALSE;
        }


        //Down
        if (state & BUTTON_DOWN)
        {
            dy=Player[ID].v;
            ny=PTRUE;
            MoveIt=PTRUE;
        }
        else if (changed & BUTTON_DOWN)
        {
            dy=0;
            ny=_FALSE;
            MoveIt=_FALSE;
        }


        //Left
        if (state & BUTTON_LEFT)
        {
            dx=Player[ID].v;
            nx=NTRUE;
            MoveIt=PTRUE;
        }
        else if (changed & BUTTON_LEFT)
        {
            dx=0;
            nx=FALSE;
            MoveIt=_FALSE;
        }


        //Right
        if (state & BUTTON_RIGHT)
        {
            dx=Player[ID].v;
            nx=PTRUE;
            MoveIt=PTRUE;
        }
        else if (changed & BUTTON_RIGHT)
        {
            dx=0;
            nx=_FALSE;
            MoveIt=_FALSE;
        }


        //A Button
        if (state & BUTTON_A)
        {
            //Increment c value, Wrap between 0 & 3
            Player[ID].c++;
            if (Player[ID].c>3)
            {
                Player[ID].c=0;
            }

            //Retrieve and set the velocity for the player
            Player[ID].v=Speeds[Set][Player[ID].c];
        }
        else if (changed & BUTTON_A)
        {
            //@NOP
        }


        //B Button
        if ((state & BUTTON_B) && (Opts[2]==PTRUE))
        {
            //if no powerups are active, then let the player activate his powerup
            if ((Player[0].aPwr==Pwr_Null) && (Player[1].aPwr==Pwr_Null))
            {
                Player[ID].aPwr=Player[ID].sPwr;    //Set active power to saved power
                Player[ID].sPwr=0;                  //Delete saved powerup (it just got used)
                //@Powerups PTRUE, P_aPwr(char), Char 'Initialize powerup's effects for the player
            }
        }
        else if (changed & BUTTON_B)
        {
            //@NOP
        }


        //C Button
        if ((state & BUTTON_C) && (DBUG == PTRUE))
        {
            //Do some debug stuff (Here, cycle saved powerups for testing)
            Player[ID].sPwr++;  //'Increment saved powerup, wrap between 0 & 11
            if (Player[ID].sPwr>Pwr_Null)
            {
                Player[ID].sPwr=Pwr_MPuck;
            }
            HUD(); //Refresh hud
        }
        else if (changed & BUTTON_C)
        {
            //@NOP
        }


        //X Button
        if (state & BUTTON_X)
        {
            Announcer();
        }
        else if (changed & BUTTON_X)
        {
            //@NOP
        }


        //Y Button
        if (state & BUTTON_Y)
        {
            //Increment player 1's score, wrap between 0 & 10
            Player[0].Score++;
            if (Player[0].Score>10)
            {
                Player[0].Score=0;
            }
            HUD();
        }
        else if (changed & BUTTON_Y)
        {
            //@NOP
        }


        //Z Button
        if (state & BUTTON_Z)
        {
            //Increment player 2's score, wrap between 0 & 10
            Player[1].Score++;
            if (Player[1].Score>10)
            {
                Player[1].Score=0;
            }
            HUD();
        }
        else if (changed & BUTTON_Z)
        {
            //@NOP
        }


        //Start button, Do Pause screen
        if (state & BUTTON_START)
        {
            Paused();
            JOY_setEventHandler(&BtnStickMove); //Restore joypad interrupt

        }
        else if (changed & BUTTON_START)
        {
            //@NOP
        }


        if (MoveIt==PTRUE)
        {
            //Move the player
            x=GameSprites[SOff_paddle+ID].x;
            y=GameSprites[SOff_paddle+ID].y;

            switch(nx)
            {
                case NTRUE:
                    x-=dx;
                    break;
                case PTRUE:
                    x+=dx;
                    break;
                default:
                    //NOP
                    break;
            }

            switch(ny)
            {
                case NTRUE:
                    y-=dy;
                    break;
                case PTRUE:
                    y+=dy;
                    break;
                default:
                    //NOP
                    break;
            }

            SPR_setPosition(&GameSprites[SOff_paddle+ID],x,y);

            //Update StickStats and show DY/DX values!
            if (DBUG==PTRUE)
            {
                StickStats(ID,dx,dy,nx,ny);
            }
            //@GetBox 1,P_hand(char),#FALSE,#FALSE,#FALSE
            //@StickCollide 'Check stick colllisions
            SPR_update(GameSprites,SOff_Total);
            MoveIt==_FALSE;
        }
    }
}

void StickStats(u8 ID, u8 dx, u8 dy, s8 nx, s8 ny)
{
    u8 x;
    char val[3][3];
    char text[15];

    if (ID==0)
    {
        x=1;
        VDP_setTextPalette(PLNPAL);
    }
    else
    {
        x=15;
        VDP_setTextPalette(OBJPAL);
    }
    VDP_setTextPlan(PLAN_B);
    VDP_setTextPriority(PTRUE);
    strclr(val[0]);
    strclr(val[1]);
    strclr(val[2]);
    strclr(val[3]);
    strclr(text);

    //X/Y coords
    VDP_drawText("X,Y",x,3);
    VDP_clearTextLine(4);
    intToStr(GameSprites[SOff_paddle+ID].x,val[0],1);
    intToStr(GameSprites[SOff_paddle+ID].y,val[1],1);
    strcpy(text, val[0]);
    strcat(text, ",");
    strcat(text, val[1]);
    VDP_drawText(text,x,4);
    strclr(val[0]);
    strclr(val[1]);
    strclr(val[2]);
    strclr(val[3]);
    strclr(text);

    //Velocity, Counter, Angle
    VDP_drawText("V, C, Angle",x,5);
    VDP_clearTextLine(6);
    uintToStr(Player[ID].v,val[0],1);
    uintToStr(Player[ID].c,val[1],1);
    uintToStr(Player[ID].ang,val[2],1);
    strcpy(text, val[0]);
    strcat(text, ",");
    strcat(text, val[1]);
    strcat(text, ",");
    strcat(text, val[2]);
    VDP_drawText(text,x,6);
    strclr(val[0]);
    strclr(val[1]);
    strclr(val[2]);
    strclr(val[3]);
    strclr(text);

    //dx/dy
    VDP_drawText("dx, dy",x,7);
    VDP_clearTextLine(8);
    uintToStr(dx,val[0],1);
    uintToStr(dy,val[1],1);

    switch(nx)
    {
        case NTRUE:
            strcpy(val[2],"-");
            break;
        case PTRUE:
            strcpy(val[2],"+");
            break;
        default:
            strcpy(val[2]," ");
            break;
    }

    switch(ny)
    {
        case NTRUE:
            strcpy(val[3],"-");
            break;
        case PTRUE:
            strcpy(val[3],"+");
            break;
        default:
            strcpy(val[3]," ");
            break;
    }

    strcpy(text,val[2]);
    strcat(text,val[0]);
    strcat(text,",");
    strcat(text,val[3]);
    strcat(text,val[1]);
    VDP_drawText(text,x,8);
    strclr(val[0]);
    strclr(val[1]);
    strclr(val[2]);
    strclr(val[3]);
    strclr(text);
}
