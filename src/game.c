#include "../inc/game.h"
#include "../inc/main.h"

//Contain Game related code

//Routine initz the game match
//Act is a bool which init/deinitz the game
void InitGame(u8 act)
{
    //Local vars
    u8 i;                    //Generic counter var #1
    u8 j;                    //Generic counter var #2
    u8 BG;                   //BG ID to load based upon difficulty

    //Init game
    if (act==PTRUE)
    {
        DrawBG(0);      //Cls
        BG=14+Opts[1];  //Get appropriate BG ID
        DrawBG(BG);     //Draw it

        //Play appropriate Song based upon difficulty
        //@Set PSong as appropriately
        switch(Opts[1])
        {
            case 0:
                echo_play_bgm(BGM_06);
                break;
            case 1:
                echo_play_bgm(BGM_05);
                break;
            case 2:
                echo_play_bgm(BGM_04);
                break;
        }

        //Setup more graphics
        SYS_disableInts();                                  //Disable interrupts
        SPR_init(384);
        VDP_resetSprites();
        VDP_setPalette(PWRPAL, SPR_Pwr.palette->data);      //Init palette PWRPAL
        VDP_setPalette(OBJPAL, SPR_ObjsN.palette->data);    //Init palette OBJPAL
        VDP_setPaletteColor(PLNPAL+15,0xE);                 //Set last entry of PLNPAL to Red, for Red text
        //@Due to palette schema, last entry of PWRPAL is blue.
        //We will switch between PLNPAL and PWRPAl to draw red/blue text where needed
        SYS_enableInts();

        //Set Player 1's spritesheet and sprite
        //@Tile uploaded, sprites don't appear. fix
        SPR_initSprite(&GameSprites[SOff_paddle], &SPR_ObjsN, 80, 96, TILE_ATTR(OBJPAL,TRUE,FALSE,FALSE));
        SPR_setFrame(&GameSprites[SOff_paddle],ON_Red);
        //@Doesn't this get initialized elsewhere?
        Player[0].Side=_FALSE;   //Set his side to left
        Player[0].alive=PTRUE;   //Set paddle to alive
        Player[0].sPwr=Pwr_Null;
        Player[0].aPwr=Pwr_Null;

        //Set Player #2's spritesheet and sprite
        //@Tile uploaded, sprites don't appear. fix
        SPR_initSprite(&GameSprites[SOff_paddle+1], &SPR_ObjsN, 240, 96, TILE_ATTR(OBJPAL,TRUE,FALSE,FALSE));
        SPR_setFrame(&GameSprites[SOff_paddle+1],ON_Blue);
        Player[1].Side=PTRUE;   //Set his side to right
        Player[1].alive=PTRUE;   //Set paddle to alive
        Player[0].sPwr=Pwr_Null;
        Player[0].aPwr=Pwr_Null;

        //Create pucks
        for (i=0;i<=(Max_Pucks-1);i++)
        {
            SPR_initSprite(&GameSprites[SOff_pucks+i], &SPR_Pwr, 148, 100, TILE_ATTR(PWRPAL,TRUE,FALSE,FALSE));
            SPR_setFrame(&GameSprites[SOff_pucks+i],SPR_Puck);
            //Hide additional pucks
            if (i!=0)
            {
                SPR_setPosition(&GameSprites[SOff_pucks+i],-128, -128);
            }
        }

        //Power HUD
        /*
        SPR_initSprite(&GameSprites[SOff_power], &SPR_Pwr, -128, -128, TILE_ATTR(PWRPAL,TRUE,FALSE,FALSE));
        SPR_setFrame(&GameSprites[SOff_power],Pwr_Null);
        SPR_initSprite(&GameSprites[SOff_spower], &SPR_Pwr, -128, -128, TILE_ATTR(PWRPAL,TRUE,FALSE,FALSE));
        SPR_setFrame(&GameSprites[SOff_spower],Pwr_Null);
        SPR_initSprite(&GameSprites[SOff_spower+1], &SPR_Pwr, -128, -128, TILE_ATTR(PWRPAL,TRUE,FALSE,FALSE));
        SPR_setFrame(&GameSprites[SOff_spower+1],Pwr_Null);
        */

        //Create Objs
        for (i=0;i<=(Max_Objs-1);i++)
        {
            //if powerups enabled
            if ((i==0) && (Opts[2]==PTRUE))
            {
                SPR_initSprite(&GameSprites[SOff_objects+i], &SPR_Pwr, -128, -128, TILE_ATTR(PWRPAL,TRUE,FALSE,FALSE));
                SPR_setFrame(&GameSprites[SOff_objects+i],Pwr_Fast);
                Objs[i].Type=OT_Pwr;
            }
            else
            {
                SPR_initSprite(&GameSprites[SOff_objects+i], &SPR_ObjsN, -128, -128, TILE_ATTR(OBJPAL,TRUE,FALSE,FALSE));
                SPR_setFrame(&GameSprites[SOff_objects+i],ON_Null);
                Objs[i].Type=OT_NULL;
            }
            Objs[i].Subtype=OST_NULL;
        }

        //Update it all!
        SPR_update(GameSprites,SOff_Total);
        //if Opts(3) = #PTRUE then Powerups #NTRUE, #FALSE, #FALSE //if powerups enabled, initialize powerup stuff
        HUD();
    }
    else
    {

    }
}

//Routine to do Announcer Guy stuff
void Announcer()
{

    //Skip if sfx disabled
    if (Opts[4] ==_FALSE)
    {
        return _FALSE;
    }

    u8 Words[7];    //The assembled sentence to say

    u8 Nums[]=      //Array to hold Number (1-10) sfx IDs
    {
        13,14,15,16,17,18,19,20,21,22
    };

    u8 Team[]=     //Array to hold team ("blue"/"red") sfx IDS
    {
        25,24
    };

    u8 Other[]=    //Array to hold everything else
    {
        23,26,27,30
    };

    u8 i;   //Generic Counter var #1

    Words[1] = Other[0]; //"to"
    if (Player[0].Score == 0)
    {
        //if player 1's score is 0
        Words[0] = 0; //Don't say player 1's score
        Words[1] = 0; //Don't even say "to" !
    }
    else
    {
        if (Player[0].Score > 10)
        {
            Words[0]=Nums[9];   //Say player 1's score #
        }
        else
        {
            Words[0]=Nums[Player[0].Score-1];
        }
    }

    //Ditto with player #2
    if (Player[1].Score==0)
    {
        Words[2]=0;
        Words[1]=0;
    }
    else
    {
        if (Player[1].Score > 10)
        {
            Words[2]=Nums[9];   //Say player 2's score #
        }
        else
        {
            Words[2]=Nums[Player[1].Score-1];
        }
    }

    //Say which player (by color) is winning
    if (Player[0].Score>Player[1].Score)
    {
        Words[3]=Team[0];
    }
    else
    {
        Words[3]=Team[1];
    }

    //if tied, don't say it
    if (Player[0].Score==Player[1].Score)
    {
        Words[3]=0;
    }

    if ((Player[0].Score==10) || (Player[1].Score==10))
    {
        Words[4] = Other[1]; //"Gameover!"
        Words[5] = Words[3]; //[Winning player color]
        Words[6] = Other[2]; //... wins"
        Words[7] = Other[3]; //[Buzzer sfx]
    }
    else
    {
        //Otherwise, nop out unused word slots for sentence
        for (i=4;i<=7;i++)
        {
            Words[i] = 0;
        }
    }

    //Speak the sentence, ala Pete Sempras' Tennis style (from Sega Genesis)
    for (i=0;i<=7;i++)
    {
        if (Words[i]!=0)
        {
            echo_wait_sfx(Sounds[Words[i]]);
        }
    }
}

//Routine to update the gameplay HUD
void HUD()
{
    u8 ID;          //Player with active powerup
    u8 x;           //VDP_draw x
    u8 y;           //VDP_draw y
    u16 Mem;        //Amt of Mem free
    u32 FPS;        //FPS of Game
    char val[10];   //Number as string

    //Setup Text plan
    VDP_setTextPlan(PLAN_B);
    VDP_setTextPriority(PTRUE);

    //if DBUG on, show FPS and MEM
    if (DBUG==PTRUE)
    {
        //Display FPS
        x=6;
        y=26;
        FPS=getFPS();
        uintToStr(FPS,val,1);
        VDP_setTextPalette(OBJPAL);
        VDP_drawText("FPS: ",1,y);
        VDP_drawText("  ",x,y);
        VDP_drawText(val,x,y);


        x=6;
        y=27;
        Mem=MEM_getFree();
        uintToStr(Mem,val,1);
        VDP_setTextPalette(PLNPAL);
        VDP_drawText("MEM: ",1,y);
        VDP_drawText("      ",x,y);
        VDP_drawText(val,x,y);
    }

    //If powerups enabled
    if (Opts[2]==PTRUE)
    {
        //Determine who is using a powerup
        if (Player[0].aPwr==Pwr_Null)
        {
            ID=0;
        }
        else
        {
            ID=1;
        }

        //Set active powerup sprites for appropriate players.
        if (ID==0)
        {
            SPR_setFrame(&GameSprites[SOff_power],Player[0].aPwr);
        }
        else
        {
            SPR_setFrame(&GameSprites[SOff_power],Player[1].aPwr);
        }

        //Set saved powerup sprites
        SPR_setFrame(&GameSprites[SOff_spower],Player[0].aPwr);
        SPR_setFrame(&GameSprites[SOff_spower+1],Player[1].aPwr);
    }

    //Display player 1's active and saved powerups on their approriate/current sides
    //Set location for player's #1's score
    //@Optimize this with vars?
    if (Player[0].Side==_FALSE)
    {
        x=1;
        y=1;

        //If powerups on
        if (Opts[2]==PTRUE)
        {
            //Set Saved powerup
            SPR_setPosition(&GameSprites[SOff_spower],24,24);

            //Set Active powerup (if applicable)
            if (ID==0)
            {
                SPR_setPosition(&GameSprites[SOff_power],24,48);
            }
        }
    }
    else
    {
        //Ditto for other side, just different coordinates
        x=38;
        y=1;

        if (Opts[2]==PTRUE)
        {
            SPR_setPosition(&GameSprites[SOff_spower],296,24);

            if (ID==0)
            {
                SPR_setPosition(&GameSprites[SOff_power],296,48);
            }
        }
    }

    //Print Player #1's score
    uintToStr(Player[0].Score,val,1);
    VDP_setTextPalette(PLNPAL);              //Set text to red
    VDP_drawText("  ",x,y);
    VDP_drawText(val,x,y);              //Draw it

    //Block similar to previous, but if/else sections swapped, indices changed, and using blue text
    if (Player[1].Side==PTRUE)
    {
        x=38;
        y=1;

        if (Opts[2]==PTRUE)
        {
            SPR_setPosition(&GameSprites[SOff_spower+1],296,24);

            if (ID==1)
            {
                SPR_setPosition(&GameSprites[SOff_power],296,48);
            }
        }
    }
    else
    {
        x=1;
        y=1;

        //If powerups on
        if (Opts[2]==PTRUE)
        {
            //Set Saved powerup
            SPR_setPosition(&GameSprites[SOff_spower+1],24,24);

            //Set Active powerup (if applicable)
            if (ID==1)
            {
                SPR_setPosition(&GameSprites[SOff_power],24,48);
            }
        }
    }

    uintToStr(Player[1].Score,val,1);
    VDP_setTextPalette(OBJPAL);
    VDP_drawText("  ",x,y);
    VDP_drawText(val,x,y);
}

//Routine to handle pausing the game!
void Paused()
{
    isPaused=PTRUE;

    u16 i;   //Generic Coutner variable #1
    u16 x=1;
    u16 y=4;

    u16 pal[]=
    {
        0x0000,0x000E,0x00E0,0x0E00,
        0x0E0E,0x00EE,0x0EE0,0x0EEE,
        0x0000,0x0000,0x0000,0x0000,
        0x0000,0x0000,0x0000,0x0000,
    };
    u16 ind=(16*MISCPAL)+15;
    u16 start;
    u16 end;


    //@Stop current song
    echo_stop_bgm();

    //Setup text
    VDP_setTextPlan(PLAN_B);
    VDP_setTextPriority(PTRUE);
    VDP_setPalette(MISCPAL,pal);
    VDP_setTextPalette(MISCPAL);

    //Draw pause text
    //            1234567890123456789012345678901234567
    VDP_drawText("+-----------------------------------+",x,y);y++;
    VDP_drawText("|#===# #===# #   # #==== #==== ====\|",x,y);y++;
    VDP_drawText("|#   # #   # #   # #     #     #   #|",x,y);y++;
    VDP_drawText("|#===+ #===# #   # #===# #==== #   #|",x,y);y++;
    VDP_drawText("|#     #   # #   #     # #     #   #|",x,y);y++;
    VDP_drawText("|#     #   # #===# ====# #==== ====/|",x,y);y++;
    VDP_drawText("+--------Press START Button---------+",x,y);y++;

    //@Everything below crashes. Why?
    //JOY_setEventHandler(&BtnPaused);
    while (isPaused==PTRUE)
    {

        for (i=1;i<=7;i++)
        {
            start=ind;
            end=(16*MISCPAL)+i;
            VDP_fade(ind,ind,start,end,1000,PTRUE);    //Fade up to color
            end=(16*MISCPAL);
            VDP_fade(ind,ind,start,end,1000,PTRUE);    //Fade down to color
            VDP_waitVSync();                            //Sync
        }
    }
    //@Resume old song
}

//Paused joy callback
void BtnPaused(u16 joy, u16 changed, u16 state)
{
    u8 i;

    if (state & BUTTON_START)
    {
        isPaused=_FALSE;
    }

    //Do puck respawn cheat
    if (state & BUTTON_C)
    {
        SPR_setPosition(&GameSprites[SOff_pucks],148, 100);

        //@NEW to retro version!!
        if ((Player[0].aPwr==Pwr_MPuck) || (Player[1].aPwr==Pwr_MPuck))
        {
            for (i=1;i<=(Max_Pucks-1);i++)
            {
                    SPR_setPosition(&GameSprites[SOff_pucks+i],148, 100);
            }
        }
    }
}
