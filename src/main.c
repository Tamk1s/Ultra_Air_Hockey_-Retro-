#include <genesis.h>
#include "../inc/main.h"
//@#include "../res/Gfx/Planes.h"
#include "../inc/game.h"
#include "../res/Gfx/Sprites.h"
#include "SpriteManip.h"
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

        //Setup appropriate joy types for speediness
        //if (DBUG==_FALSE)
        //{
            //JOY_setSupport(PORT_1, JOY_SUPPORT_3BTN);
        //}
        //else
        //{
            JOY_setSupport(PORT_1, JOY_SUPPORT_6BTN);
        //}


        //if (Opts[0]==_FALSE)
        //{
            //JOY_setSupport(PORT_2, JOY_SUPPORT_OFF);
        //}
        //else
        //{
            //if (DBUG==_FALSE)
            //{
                //JOY_setSupport(PORT_2, JOY_SUPPORT_3BTN);
            //}
            //else
            //{
                JOY_setSupport(PORT_2, JOY_SUPPORT_6BTN);
            //}
        //}
        JOY_setEventHandler(BtnStick);    //Setup skip joy handler

        while(1)
        {
            BtnStickMove(JOY_1, JOY_readJoypad(JOY_1));
            //if (Opts[0]==PTRUE)
            //{
                BtnStickMove(JOY_2, JOY_readJoypad(JOY_2));
            //}
            //else
            //{
                //@Goto CPU Stick function here
            //}

            //if (DBUG==PTRUE)
            //{
            HUD();
            //}
            VDP_waitVSync();                        //Sync
        }
    }
}

void BtnStick(u16 joy, u16 changed, u16 state)
{
    u8 Set=0;
    u8 ID=0;
    u8 MoveIt=_FALSE;
    //@Last slot speeds are not working? Also, on init, red puck blasts off into space
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
    //if (Player[ID].alive==PTRUE)
    //{
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

        //B Button
        if ((state & BUTTON_B) && (Opts[2]==PTRUE))
        {
            //if no powerups are active, then let the player activate his powerup
            if ((Player[0].aPwr==Pwr_Null) && (Player[1].aPwr==Pwr_Null))
            {
                Player[ID].aPwr=Player[ID].sPwr;    //Set active power to saved power
                Player[ID].sPwr=0;                  //Delete saved powerup (it just got used)
                HUD();
                //@Powerups PTRUE, P_aPwr(char), Char 'Initialize powerup's effects for the player
            }
        }

        //if (DBUG==PTRUE)
        //{

            //C Button
            if ((state & BUTTON_C)&& (Opts[2]==PTRUE))
            {
                //Do some debug stuff (Here, cycle saved powerups for testing)
                Player[ID].sPwr++;  //'Increment saved powerup, wrap between 0 & 11
                if (Player[ID].sPwr>Pwr_Null)
                {
                    Player[ID].sPwr=Pwr_MPuck;
                }
                HUD(); //Refresh hud
            }

            //X Button
            if (state & BUTTON_X)
            {
                Announcer();
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
        //}

        //Start button, Do Pause screen
        if (state & BUTTON_START)
        {
            Paused();
            JOY_setEventHandler(BtnStickMove); //Restore joypad interrupt
        }
    //}
}

void BtnStickMove(u8 numjoy, u16 value)
{
    u8 dx=0;
    u8 dy=0;
    s8 nx=_FALSE;
    s8 ny=_FALSE;
    s16 x=0;
    s16 y=0;
    u8 ID=0;

    u8 MoveIt=_FALSE;

    if (numjoy==JOY_1)
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
        if (value & BUTTON_UP)
        {
            dy=Player[ID].v;
            ny=NTRUE;
            MoveIt=PTRUE;
        }
        else if (value & BUTTON_DOWN)
        {
            dy=Player[ID].v;
            ny=PTRUE;
            MoveIt=PTRUE;
        }

        //Left
        if (value & BUTTON_LEFT)
        {
            dx=Player[ID].v;
            nx=NTRUE;
            MoveIt=PTRUE;
        }
        else if (value & BUTTON_RIGHT)
        {
            dx=Player[ID].v;
            nx=PTRUE;
            MoveIt=PTRUE;
        }

        if (MoveIt==PTRUE)
        {
            //Move the player
            x=(&GameSprites[SOff_paddle+ID])->x;
            y=(&GameSprites[SOff_paddle+ID])->y;
            x-=0x80;
            y-=0x80;

            switch(nx)
            {
            case NTRUE:
                x-=dx;
                break;
            case PTRUE:
                x+=dx;
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
            }

            SPR_setPosition(&GameSprites[SOff_paddle+ID],x,y);

            //Update StickStats and show DY/DX values!
            if (DBUG==PTRUE)
            {
                StickStats(ID,dx,dy,nx,ny);
            }
            //@GetBox 1,P_hand(char),#FALSE,#FALSE,#FALSE
            StickCollide(ID);   //Check stick colllisions
            SPR_update(GameSprites,SOff_Total);
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

/*Routine to check collision between sticks &
  objects, pucks, centerline, and border
  ID=player to process*/
void StickCollide(u8 ID)
{
    u8 i;          //Generic counter variable #1
    u8 Hit;        //Was there a collision?
    u8 *Hit_Sfx=0; //Hit sfx pointer
    u16 offset[2]; //Temp register for pixel calcs
    _Box box[1];   //Boxes to compare against

    //Process the player

    //Change border collision sfx dependent on if Big or little stick
    if (Player[ID].aPwr==Pwr_BStick)
    {
        Hit_Sfx=&SFX_30;
    }
    else
    {
        Hit_Sfx=&SFX_04;
    }

    //Get sprite vars for player being processed. Use as box[0]. box[1]=thing collided with
    box[0]=GetBox(&GameSprites[SOff_paddle+ID]);

    //Check board bounds

	//Left border
	offset[0]=SPR_Origin+2;
    if (box[0].x1<=offset[0])
    {
        offset[1]=SPR_Origin+3;
        offset[2]=box[0].y1;
        offset[1]-=0x80;
        offset[2]-=0x80;
        SPR_setPosition(&GameSprites[SOff_paddle+ID], offset[1], offset[2]);    //Fix OOB Collision
        box[0]=GetBox(&GameSprites[SOff_paddle+ID]);       //Update Box
        echo_play_sfx(Hit_Sfx);
    }

    //Same idea for top, right, and bottom borders
    //Top border
    offset[0]=SPR_Origin+2;
    if (box[0].y1<=offset[0])
    {
        offset[1]=box[0].x1;
        offset[2]=SPR_Origin+3;
        offset[1]-=0x80;
        offset[2]-=0x80;
        SPR_setPosition(&GameSprites[SOff_paddle+ID], offset[1], offset[2]);
        box[0]=GetBox(&GameSprites[SOff_paddle+ID]);
        echo_play_sfx(Hit_Sfx);
    }

	//Right border
	offset[0]=(SPR_Origin+VDP_Width)-2;
    if (box[0].x2>=offset[0])
    {
        offset[1]=(SPR_Origin+VDP_Width)-(box[0].w+2);
        offset[2]=box[0].y1;
        offset[1]-=0x80;
        offset[2]-=0x80;
        SPR_setPosition(&GameSprites[SOff_paddle+ID], offset[1], offset[2]);
        box[0]=GetBox(&GameSprites[SOff_paddle+ID]);
        echo_play_sfx(Hit_Sfx);
    }

	//Bottom border
	offset[0]=(SPR_Origin+VDP_Height)-2;
    if (box[0].y2>=offset[0])
    {
        offset[1]=box[0].x1;
        offset[2]=(SPR_Origin+VDP_Height)-(box[0].h+2);
        offset[1]-=0x80;
        offset[2]-=0x80;
        SPR_setPosition(&GameSprites[SOff_paddle+ID], offset[1], offset[2]);
        box[0]=GetBox(&GameSprites[SOff_paddle+ID]);
        echo_play_sfx(Hit_Sfx);
    }

    if (DBUG==_FALSE)
    {
        //Check center line bounds
        if (Player[ID].Side==_FALSE)
        {
            //if on left side, prevent player from going onto right side
            offset[0]=SPR_Origin+VDP_HWidth;
            if (box[0].x2>=offset[0])
            {
                offset[1]=(SPR_Origin+VDP_HWidth)-(box[0].w+1);
                offset[2]=box[0].y1;
                offset[1]-=0x80;
                offset[2]-=0x80;
                SPR_setPosition(&GameSprites[SOff_paddle+ID], offset[1],offset[2]);
                box[0]=GetBox(&GameSprites[SOff_paddle+ID]); //Update box
            }
        }
        else
        {
            //if on right side, prevent player from going onto left side
            offset[0]=SPR_Origin+VDP_HWidth;
            if (box[0].x1<=offset[0])
            {
                offset[1]=SPR_Origin+VDP_HWidth+1;
                offset[2]=box[0].y1;
                offset[1]-=0x80;
                offset[2]-=0x80;
                SPR_setPosition(&GameSprites[SOff_paddle+ID], offset[1],offset[2]);
                box[0]=GetBox(&GameSprites[SOff_paddle+ID]); //Update box
            }
        }
    }

    /*
    '@Disabled until get general collision detection working!
    if #PTRUE=#FALSE then
    'Check for collisions
    'TRAPCPU
    GetBox 1, P_hand(P), #PTRUE, P_angle(P), P_v(P)
    'TRAPCPU
    Hit=GSpriteCollide(#PTRUE,Box_hand(1),#FALSE,#FALSE,#FALSE)
    IF hit=#PTRUE then

        'Check object collisions (bumpers and wall only)
        FOR Ctr1 = 1 to #N_OBJS
            'i_f (SPRITECOLLIDEWITH(Box_hand(1)) = Objs(Ctr1).hand) AND (Objs(Ctr1).Type = 1 OR Objs(Ctr1).Type = 2) then
                GetBox 2, OB_hand(Ctr1), #PTRUE, #FALSE, #FALSE 'Get sprite vars for collided object
                'Do the collision, with appropriate sound effect
                'i_f OB_Type(Ctr1)= 1 then StdCol Pt(), 0, #FALSE, 5 else StdCol Pt(), 0, #FALSE, 4
            'endi_f
        NEXT Ctr1

        'Check primary puck collision
        'This code enables powerup collection
        if Opts(3)=#PTRUE then
            'i_f SPRITECOLLIDEWITH(Box_hand(1)) = Pucks&(1) then
                P_Hitter(P) = #PTRUE 'Set player as hitter
                'Make other NOT hitter
                if P = 1 then P_Hitter(2)=#FALSE else P_Hitter(1)=#FALSE
            'endi_f
        ENDIF
    ENDIF
    endif

 next P
 */
}
