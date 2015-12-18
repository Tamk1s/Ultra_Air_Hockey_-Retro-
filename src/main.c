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

        Opts[0]=_FALSE;          // !@ Remove me after debugging
        if (Opts[0]==_FALSE)
        {
            JOY_setSupport(PORT_2, JOY_SUPPORT_OFF);

        }
        //else
        //{
            //if (DBUG==_FALSE)
            //{
                //JOY_setSupport(PORT_2, JOY_SUPPORT_3BTN);
            //}
            //else
            //{
              //  JOY_setSupport(PORT_2, JOY_SUPPORT_6BTN);
            //}
        //}
        JOY_setEventHandler(BtnStick);    //Setup skip joy handler

        while((Player[0].Score<10)&&(Player[1].Score<10))
        {
            PuckMove(2,Pux[0],V2D_s16_Zero);    //Display all pucks
            PuckMove(0,Pux[0],V2D_s16_Zero);    //Move all pucks
            BtnStickMove(JOY_1, JOY_readJoypad(JOY_1));
            //if (Opts[0]==PTRUE)
            //{
                // !@ This does not work. Refactor into BtnStick?
                //BtnStickMove(JOY_2, JOY_readJoypad(JOY_2));
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
            JOY_setEventHandler(BtnStick); //Restore joypad interrupt
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
    //if (Player[ID].alive==PTRUE)
    //{

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
            x-=SPR_Origin;
            y-=SPR_Origin;

            switch(nx)
            {
            case NTRUE:
                Player[ID].ang.x=0-dx;
                x-=dx;
                break;
            case PTRUE:
                Player[ID].ang.x=dx;
                x+=dx;
                break;
            }

            switch(ny)
            {
            case NTRUE:
                Player[ID].ang.y=0-dy;
                y-=dy;
                break;
            case PTRUE:
                Player[ID].ang.y=dy;
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
    //}
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
    //uintToStr(Player[ID].ang,val[2],1);
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
        offset[1]-=SPR_Origin;
        offset[2]-=SPR_Origin;
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
        offset[1]-=SPR_Origin;
        offset[2]-=SPR_Origin;
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
        offset[1]-=SPR_Origin;
        offset[2]-=SPR_Origin;
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
        offset[1]-=SPR_Origin;
        offset[2]-=SPR_Origin;
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
                offset[1]-=SPR_Origin;
                offset[2]-=SPR_Origin;
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
                offset[1]-=SPR_Origin;
                offset[2]-=SPR_Origin;
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

//Routine to make all pucks move
void PuckMove(u8 act, Puck pux, Vect2D_s16 Ang)
{
/*
Act=
0=Move all
1=Stop a puck, change its dir/spd, reupdate
2=Display all pucks
*/

    u8 i;   //Generic counter var
    u8 max; //Max pucks to process
    u16 x,y;

    //Set amount of pucks to process
    if ((Player[0].aPwr==Pwr_MPuck)||(Player[1].aPwr==Pwr_MPuck))
    {
        max=Max_Pucks;
    }
    else
    {
        max=1;
    }

    //Dipslay the pucks
    if (act==2)
    {
        SPR_update(GameSprites,SOff_Total);
    }
    else
    {
        //Change direction of puck
        if ((act==1)&&((Ang.x!=0)&&(Ang.y!=0)))
        {
            pux.v.x=0;
            pux.v.y=0;
            pux.v.x=Ang.x;
            pux.v.y=Ang.y;
        }

        //Move all pucks
        for (i=0;i<=Max_Pucks;i++)
        {
            x=GameSprites[SOff_pucks+i].x;
            y=GameSprites[SOff_pucks+i].y;
            x+=Pux[i].v.x;
            y+=Pux[i].v.y;
            x-=SPR_Origin;
            y-=SPR_Origin;
            SPR_setPosition(&(GameSprites[SOff_pucks+i]),x,y);
            if (act==0)
            {
                PuckCollide();
            }
        }
    }
}

//Routine to check and handle puck collisions
void PuckCollide()
{
    _Box Pt[2];
    u16 ymin;
    u16 ymax;
    u16 delta;
    u8 Goal=_FALSE;
    u8 Hit=_FALSE;
    u8 T;

    u8 i,j;
    u16 x,y;
    u8 ID;

    // !@ Buggy?
    Opts[1]=2;      // !@
    switch(Opts[1])
    {
        case 0:
            delta=30;
            break;
        case 1:
            delta=64;
            break;
        case 2:
            delta=80;
            break;
    }

    ymin = SPR_Origin + (VDP_HHeight - delta); //Set min y value of goal
    ymax = SPR_Origin + (VDP_HHeight + delta);  //Set max y ~

    for (ID=0;ID<=Max_Pucks;ID++)
    {
        if (Pux[ID].active==PTRUE)
        {
            Pt[0]=GetBox(&(GameSprites[SOff_pucks+ID]));
            Goal=_FALSE;

            //Check for goal on left side
            if (Goal==_FALSE)
            {
                if ((Pt[0].x1<=SPR_Origin+3)&&((Pt[0].y1>=ymin)&&(Pt[0].y2<=ymax)))
                {
                    //Allocate goal to appropriate player, dependent on who is on what side
                    if (Player[0].Side==_FALSE)
                    {
                        Player[1].Score++;
                    }
                    else
                    {
                        Player[0].Score++;
                    }
                    GoalSink();
                    Goal=PTRUE;
                }
            }

            //Ditto for goal on right side
            // !@ This is not working
            /*
            if (Goal==_FALSE)
            {
                if ((Pt[0].x2>=SPR_Origin+(VDP_Width-3))&&((Pt[0].y1>=ymin)&&(Pt[0].y2<=ymax)))
                {
                    if (Player[1].Side==PTRUE)
                    {
                        Player[0].Score++;
                    }
                    else
                    {
                        Player[1].Score++;
                    }
                }
                GoalSink();
                Goal=PTRUE;
            }
            */

            //Check border collisions
            if (Goal==_FALSE)
            {
                //Left border
                if (Pt[0].x1<=SPR_Origin+2)
                {
                    //Fix position
                    Pux[ID].v.x*=-1;
                    x=SPR_Origin+5;
                    y=Pt[0].y1;
                    x-=SPR_Origin;
                    y-=SPR_Origin;
                    SPR_setPosition(&(GameSprites[SOff_pucks+ID]),x,y);
                    echo_play_sfx(SFX_04);
                }

                //Same idea for other borders
                //Top border
                if (Pt[0].y1<=SPR_Origin+2)
                {
                    //Fix position
                    Pux[ID].v.y*=-1;
                    x=Pt[0].x1;
                    y=SPR_Origin+5;
                    x-=SPR_Origin;
                    y-=SPR_Origin;
                    SPR_setPosition(&(GameSprites[SOff_pucks+ID]),x,y);
                    echo_play_sfx(SFX_04);
                }

                //Right border
                if (Pt[0].x2>=SPR_Origin+(VDP_Width-2))
                {
                    //Fix position
                    Pux[ID].v.x*=-1;
                    x=SPR_Origin+(VDP_Width-(Pt[0].w+5));
                    y=Pt[0].y1;
                    x-=SPR_Origin;
                    y-=SPR_Origin;
                    SPR_setPosition(&(GameSprites[SOff_pucks+ID]),x,y);
                    echo_play_sfx(SFX_04);
                }

                //Bottom border
                if (Pt[0].y2>=SPR_Origin+(VDP_Height-2))
                {
                    //Fix position
                    Pux[ID].v.y*=-1;
                    x=Pt[0].x1;
                    y=SPR_Origin+(VDP_Height-(Pt[0].h+5));
                    x-=SPR_Origin;
                    y-=SPR_Origin;
                    SPR_setPosition(&(GameSprites[SOff_pucks+ID]),x,y);
                    echo_play_sfx(SFX_04);
                }

                Pt[0]=GetBox(&(GameSprites[SOff_pucks+ID]));    //Update the box
                // !@Do inter-puck collision here
                // !@Do object collision here

                //Check player stick collisions
                for (i=0;i<=1;i++)
                {
                    Pt[1]=GetBox(&(GameSprites[SOff_pucks+ID]));
                    Pt[0]=GetBox(&(GameSprites[SOff_paddle+i]));    //Stick
                    Hit=CheckCollision(&Pt);
                    if (Hit==PTRUE)
                    {
                        StdCol(&Pt, 2, ID, &SFX_03);
                        PuckMove(1,Pux[ID],V2D_s16_Zero);
                    }
                }
            }
        }
    }
}

//Routine to process a goal
void GoalSink()
{
    echo_play_sfx(SFX_29);  //"Goal!"
    if (Player[0].aPwr==Pwr_MPuck)
    {
        // !@ Do multipluck stuff here
    }
    else
    {
        //Normal puck sinking (no multi-puck)
        echo_wait_sfx(SFX_08);  //Do Siren sfx, with pause

        //Stop primary puck's motion, place at center
        Pux[0].v.x=0;
        Pux[0].v.y=0;
        SPR_setPosition(&(GameSprites[SOff_pucks]),VDP_HWidth-12,VDP_HHeight-12);

        // !@ Disable effects of swap players and kill player powerups upon goal (here)
        HUD();          //Update HUD
        Announcer();    //Announcer guy stuff
        //Reset player positions
        SPR_setPosition(&GameSprites[SOff_paddle],80-16,128-16);
        SPR_setPosition(&GameSprites[SOff_paddle+1],240-16,128-16);
    }
}
