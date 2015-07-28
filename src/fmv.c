//Holds EagleSoft Ltd and Title FMV sequences
#include "../inc/fmv.h"
//EagleSoft Ltd FMV Sequence
void FMV()
{
    u16 x=0;            //x value of Eagle Sprite
    Sprite sprites[1];  //Sprite struct

    DrawBG(0);                                  //cls

    SYS_disableInts();                          //Disable interrupts
    VDP_setScreenWidth320();                    //320x224 VDP mode
    echo_play_sfx(SFX_33);                      //Play EagleSoft Ltd sfx song
    DrawBG(18);                                 //Draw EagleSoft Ltd BG (Plane A)
    SYS_enableInts();                           //Enable interrupts

    //Sprite stuff
    SPR_init(16);                                                                       //Init sprite tile cache to 16 tiles
    VDP_setPalette(PWRPAL, SPR_Eagle.palette->data);                                      //Init palette PWRPAL to Eagle palette
    SPR_initSprite(&sprites[0], &SPR_Eagle, x, 128, TILE_ATTR(PWRPAL,TRUE,FALSE,FALSE));  //Init the Eagle Sprite
    JOY_setEventHandler( &BtnSkip );                                                    //Setup skip joy handler

    //Move the Eagle from left to right on screen
    for (x=0;x<=320;x++)
    {
            SPR_setPosition(&sprites[0],x,128);     //Set new position
            SPR_update(sprites, 1);                 //Update it
            VDP_waitVSync();                        //Sync

            //if Skipping, hide Eagle off screen, and escape FOR loop
            if (Skip==PTRUE)
            {
                SPR_setPosition(&sprites[0],-128,-128);   //Set new position
                break;
            }
    }

    VDP_resetSprites();

    //If did not skip
    if (Skip==_FALSE)
    {
        DrawBG(19);                 //Draw plane B of EagleSoft Ltd (text/logo)
        waitMs(1000);               //Wait 1s
        SPR_end;                    //Kill sprite engine

        //Show Anniversary Logo

        //Clear A & B VDP Planes
        VDP_clearPlan(APLAN,0);
        VDP_clearPlan(BPLAN,0);
        DrawBG(20);                 //Draw Anniversary logo
        waitMs(2000);               //Wait 1s
        VDP_fadeOutAll(1000,0);     //Fade in 1s
    }
    else
    {
        //if skipped
        DrawBG(0);                                  //cls
        SPR_setPosition(&sprites[0],-128,-128);     //Hide Eagle
        SPR_update(sprites, 1);                     //Update it
        SPR_end;                                    //Kill sprite engine
    }
}

//Does Title FMV sequence
void Title()
{
    u8 ID=0;        //Screen ID#
    u16 Time=0;     //Time to wait, in MS

    //If DBUG is off, do...
    if (DBUG==_FALSE)
    {
        DrawBG(0);                  //cls
        echo_play_bgm(BGM_01);      //Play HockeyFever (Intro) song
        Time=2000;                  //Set wait time to 2s

        //Iterate between screens #1 to #7
        for (ID=1;ID<=7;ID++)
        {
            //If skipping, escape FOR loop
            if (Skip==PTRUE)
            {
                    break;
            }

            //If Screen #4, change time to 11s
            if (ID==4)
            {
                Time=11000;
            }
            waitMs(Time);   //Wait
            DrawBG(ID);     //Draw the new BG
        }
    }
}

//Joy handler for skipping stuff
void BtnSkip(u16 joy, u16 changed, u16 state)
{
    if (joy == JOY_1)
    {
        //If Start pressed, flag skip; else if released unflag
        if (state & BUTTON_START)
        {
            Skip=PTRUE;
        }
        else if (changed & BUTTON_START)
        {
            Skip=_FALSE;
        }
    }
}
