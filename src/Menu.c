#include "../inc/Menu.h"


//Processes Main Menu
void MainMenu()
{
    u8 Done=_FALSE;

    DrawBG(7);
    if (DBUG==_FALSE)
    {
        echo_wait_sfx(SFX_09);  //"Ultra Air Hockey!"
        echo_wait_sfx(SFX_08);  //Siren
    }

    Trig=PTRUE;
    //Loop until Done is PTRUE
    while (Done==_FALSE)
    {

        echo_play_bgm(BGM_02);              //Play HockeyFever (Loop)
        InitMenu(1,0,0,4,PTRUE);            //Init menu to 3 items
        JOY_setEventHandler(&BtnHMenu);   //Set appropriate button handler

        //While nothing is selected
        while (SItem==0)
        {
            VDP_waitVSync();
            //If a dir key was pressed, update the background to reflect highlighted choice
            if (Trig==PTRUE)
            {
                DrawBG(10+HItem);
            }
        }

        //Process the selected item
        switch (SItem)
        {
            //Play
            case 1:
                VDP_fadeOutAll(100,_FALSE);
                ChrselMenu();   //Do Char selection menu
                Done=PTRUE;
                break;

            //Options
            case 2:
                echo_wait_sfx(SFX_11);      //"Options"
                VDP_fadeOutAll(100,_FALSE);
                OptionsMenu();
                Trig=PTRUE;
                break;

            //Credits
            case 3:
                echo_wait_sfx(SFX_12);      //"Credits"
                VDP_fadeOutAll(100,_FALSE);
                Credits();
                Trig=PTRUE;
                break;
        }
    }
    JOY_setEventHandler( &BtnNada );    //Remove button handler
}

//Inits a horizontal menu setup
//h=Hilighted Item ID
//s=Selected ~
//a=lower Item ID bound
//b=upper ~
//bool Ignore, if _FALSE set Trig to false; else ignore
void InitMenu(u8 h, u8 s, u8 a, u8 b, u8 ignore)
{
    HItem=h;
    SItem=s;
    MMin=a;
    MMax=b;
    if (ignore==_FALSE)
    {
        Trig=_FALSE;
    }
}

//Empty joy handler
void BtnNada(u16 joy, u16 changed, u16 state)
{

}

//Joy handler for horizontal menu
void BtnHMenu(u16 joy, u16 changed, u16 state)
{
    if (joy == JOY_1)
    {
        //If Left pressed
        if (state & BUTTON_LEFT)
        {
            echo_wait_sfx(SFX_01);  //HiLite
            HItem--;                //Decrement HItem and wrap if necessary
            if (HItem<=MMin)
            {
                HItem=MMax-1;
            }
            Trig=_FALSE;
        }
        //if left released
        else if (changed & BUTTON_LEFT)
        {
            Trig=PTRUE;
        }

        //If Right button pressed
        if (state & BUTTON_RIGHT)
        {
            echo_wait_sfx(SFX_01);  //HiLite
            HItem++;                //Increment HItem, wrap if necessary
            if (HItem>=MMax)
            {
                HItem=MMin+1;
            }
            Trig=_FALSE;
        }
        else if (changed & BUTTON_RIGHT)
        {
            Trig=PTRUE;
        }

        //If Start pressed
        if (state & BUTTON_START)
        {
            echo_wait_sfx(SFX_02);  //Select
            SItem=HItem;            //Set SItem to HItem
            DrawBG(0);              //Cls
        }
    }
}

//Character selection menu
//@Fix glitchy BG screen and display of Arrow
void ChrselMenu()
{
    Sprite sprites[1];  //Sprite struct

    DrawBG(0);          //Cls
    DrawBG(8);          //Draw "How many players" BG
    InitMenu(1,0,0,3,_FALSE);   //Init a 2 item Menu

    //Setup the arrow sprite
    SYS_disableInts();
    SPR_init(16);   //Sprite tile cache of 16 tiles
    SYS_enableInts();

    // !@ Screws up
    //SPR_initSprite(&sprites[0], &SPR_Arrow, 271, 266, TILE_ATTR(MISCPAL,TRUE,FALSE,FALSE));      //Init the Arrow Sprite
    //VDP_setPalette(MISCPAL, SPR_Arrow.palette->data);                                              //Init pal OBJPAL to Arrow pal

    echo_play_sfx(SFX_13);              //"How many players are going to play today?"
    JOY_setEventHandler( &BtnHMenu );   //Setup joy handler to HMenu type
    //While no items are selected
    while (SItem==0)
    {
        //If 1 player hilighted
        if ((HItem==1) && (Trig==_FALSE))
        {
            SPR_setPosition(&sprites[0],271,266);   //Set new arrow position
            SPR_update(sprites, 1);                 //Update it
        }
        else
        {
            SPR_setPosition(&sprites[0],311, 266);
            SPR_update(sprites, 1);
        }
        VDP_waitVSync();
    }

    VDP_resetSprites();

    //@Toggle amt of players as appropriately
    if (SItem==1)
    {
        Opts[0]=_FALSE;
    }
    else
    {
        Opts[0]=PTRUE;
    }

    SPR_setPosition(&sprites[0],-128, -128);    //@Kill sprite
    SPR_update(sprites, 1);                     //Update it
    SPR_end;                                    //Kill sprite engine

    echo_wait_sfx(SFX_10);                      //"Let us play some hockey!"
    VDP_fadeOutAll(100,_FALSE);
}

//Processes Options Menu
void OptionsMenu()
{
    DrawBG(0);              //cls
    echo_play_bgm(BGM_03);  //Play Nes_Mes2
    DrawBG(9);

    //Init text plane (Plane, text prio, text colors)
    VDP_setTextPlan(PLAN_B);
    VDP_setTextPriority(PTRUE);
    VDP_setPaletteColor((OBJPAL * 16)+15,0xE);    //Non higlited color
    VDP_setPaletteColor((PWRPAL * 16)+15,0xEE);   //Hilited color
    VDP_setTextPalette(OBJPAL);

    InitMenu(1,0,0,7,_FALSE);                   //Init a 6 item menu
    S_ID=0;
    M_ID=0;

    //Set joy handler to Options type
    JOY_setEventHandler( &BtnOptions );

    while (SItem==0)
    {
        VDP_waitVSync();
    }
    DrawBG(0);  //cls
}

//Handles the Options menu selections
void BtnOptions(u16 joy, u16 changed, u16 state)
{
    u8 Vert=_FALSE;     //Flag if vert menu item was changed
    u8 Horiz=_FALSE;    //~       horiz ~
    char val[2];        //String holding Sound/Music test ID
    char name[25];      //String ~       Name of the sfx/music
    u8 i=0;             //Generic counter var
    u8 pal=2;           //Active palette to use (OBJPAL or PWRPAL)

    if (joy == JOY_1)
    {
        //If up pressed
        if (state & BUTTON_UP)
        {
            echo_play_sfx(SFX_01);  //HiLite
            HItem--;                //Decrement HItem, wrap if needed
            if (HItem<=MMin)
            {
                HItem=MMax-1;
            }
            //Set vert/horiz as changed
            Vert=PTRUE;
            Horiz=PTRUE;
        }
        //if up released
        else if (changed & BUTTON_UP)
        {
            //Set vert/horiz as unchanged
            Vert=_FALSE;
            Horiz=_FALSE;
        }

        //If down pressed
        if (state & BUTTON_DOWN)
        {
            echo_play_sfx(SFX_01);  //HiLite sfx
            HItem++;                //Increment
            if (HItem>=MMax)
            {
                HItem=MMin+1;
            }
            Vert=PTRUE;
            Horiz=PTRUE;
        }
        else if (changed & BUTTON_RIGHT)
        {
            Vert=_FALSE;
            Horiz=_FALSE;
        }

        //if left pressed
        if (state & BUTTON_LEFT)
        {
            //Process each for HItem row
            if (HItem==1)
            {
                //Decrement Opts[1], wrap if necessary
                Opts[1]--;
                if (Opts[1]==255)
                {
                    Opts[1]=2;
                }
            }

            //Toggle bool (!bool)
            if ((HItem>=2) && (HItem<=4))
            {
                if (Opts[HItem]==_FALSE)
                {
                    Opts[HItem]=PTRUE;
                }
                else
                {
                    Opts[HItem]=_FALSE;
                }

                //If toggling music
                if (HItem==3)
                {
                    //If false, stop BGM; else play Nes_Mes2 again
                    if (Opts[HItem]==_FALSE)
                    {
                        echo_stop_bgm();
                    }
                    else
                    {
                        echo_play_bgm(BGM_03);
                    }
                }
            }

            //If Sound test
            if (HItem==6)
            {
                //Decremenet S_ID, wrap if necessary
                S_ID--;
                if (S_ID<0)
                {
                    S_ID=S_Max;
                }
            }

            //If music test, decrement M_ID, wrap if necessary
            if (HItem==5)
            {
                M_ID--;
                if (M_ID<0)
                {
                    M_ID=M_Max;
                }
            }

            echo_play_sfx(SFX_02);  //Select
            Horiz=PTRUE;            //Flag horiz as changed
        }
        //If released
        else if (changed & BUTTON_LEFT)
        {
            Horiz=_FALSE;   //Unflag Horiz
        }

        //If right pressed
        if (state & BUTTON_RIGHT)
        {
            //Process each HItem row
            //Difficulty, increment, wrap as necessary
            if (HItem==1)
            {
                Opts[1]++;
                if (Opts[1]>2)
                {
                    Opts[1]=_FALSE;
                }
            }

            //Toggle bools (!bool)
            if ((HItem>=2) && (HItem<=4))
            {
                if (Opts[HItem]==_FALSE)
                {
                    Opts[HItem]=PTRUE;
                }
                else
                {
                    Opts[HItem]=_FALSE;
                }

                //If toggling music, stop bgm if false; else play Nes_Mes2
                if (HItem==3)
                {
                    if (Opts[HItem]==_FALSE)
                    {
                        echo_stop_bgm();
                    }
                    else
                    {
                        echo_play_bgm(BGM_03);
                    }
                }
            }

            //If Sound test, increment S_ID, wrap if necessary
            if (HItem==6)
            {
                S_ID++;
                if (S_ID>S_Max)
                {
                    S_ID=0;
                }
            }

            //If Music test, increment M_ID, wrap if necessary
            if (HItem==5)
            {
                M_ID++;
                if (M_ID>M_Max)
                {
                    M_ID=0;
                }
            }

            echo_play_sfx(SFX_02);  //Select sfx
            Horiz=PTRUE;            //Flag Horiz as changed
        }
        //if released, unflag horiz
        else if (changed & BUTTON_RIGHT)
        {
            Horiz=_FALSE;
        }


        //If A button pressed
        if (state & BUTTON_A)
        {
            //If Sound test, play the selected S_ID
            if (HItem==6)
            {
                echo_play_sfx(Sounds[S_ID]);
            }

            //if Music test, play the selected M_ID
            if (HItem==5)
            {
                echo_play_bgm(Songs[M_ID]);
            }
        }

        //If Start button pressed
        if (state & BUTTON_START)
        {
            echo_play_sfx(SFX_03);  //Play hockey deflect sfx
            SItem=1;                //Select item
        }

        //If vert changed
        if (Vert==PTRUE)
        {
            //Clear text rows
            for (i=10;i<=16;i++)
            {
                VDP_clearText(5, i, 1);
            }

            //Set to PWRPAL
            VDP_setTextPalette(PWRPAL);
            VDP_drawText(">",5,HItem+10);   //Disp hilighted row
        }

        //If Horiz changed
        if (Horiz==PTRUE)
        {
            //Get/set appropriate palette
            if (HItem==1){pal=PWRPAL;}else{pal=OBJPAL;}
            VDP_setTextPalette(pal);

            //Draw difficulty text and selected difficulty
            VDP_drawText("Difficulty:",6,11);
            VDP_drawText("      ",20,11);
            switch(Opts[1])
            {
                case 0:
                    VDP_drawText("Easy",20,11);
                    break;
                case 1:
                    VDP_drawText("Medium",20,11);
                    break;
                case 2:
                    VDP_drawText("Hard",20,11);
                    break;
            }

            //Get/set palettes, show lables for powerups, music, and sound toggles
            if (HItem==2){pal=PWRPAL;}else{pal=OBJPAL;}
            VDP_setTextPalette(pal);
            VDP_drawText("Powerups",6,12);

            if (HItem==3){pal=PWRPAL;}else{pal=OBJPAL;}
            VDP_setTextPalette(pal);
            VDP_drawText("Music:",6,13);

            if (HItem==4){pal=PWRPAL;}else{pal=OBJPAL;}
            VDP_setTextPalette(pal);
            VDP_drawText("Sfx:",6,14);

            //Show selected boolean states for them, with appropriate palette
            for (i=2;i<=4;i++)
            {
                if (HItem==i){pal=PWRPAL;}else{pal=OBJPAL;}
                VDP_setTextPalette(pal);
                if (Opts[i]==_FALSE)
                {
                    VDP_drawText("OFF",20,10+i);
                }
                else
                {
                    VDP_drawText("ON ",20,10+i);
                }
            }

            //Ditto for Music test
            if (HItem==5){pal=PWRPAL;}else{pal=OBJPAL;}
            VDP_setTextPalette(pal);
            VDP_drawText("Music test:",6,15);
            VDP_drawText("  ",20,15);
            intToStr(M_ID,val,1);       //Convert M_ID to string
            VDP_drawText(val,20,15);    //Display it

            //Ditto for Sound test
            if (HItem==6){pal=PWRPAL;}else{pal=OBJPAL;}
            VDP_setTextPalette(pal);
            VDP_drawText("Sound test:",6,16);
            VDP_drawText("  ",20,16);
            intToStr(S_ID,val,1);
            VDP_drawText(val,20,16);

            //If Sound/music test
            if ((HItem==5)||(HItem==6))
            {
                //Fetch and show the music/sound name
                VDP_setTextPalette(PWRPAL);
                if (HItem==5)
                {
                    VDP_drawText("Song title: ",6,18);
                    VDP_drawText("                                  ",6,19);
                    VDP_drawText(Song_Names[M_ID],6,19);//@Get song title here
                }
                else
                {
                    VDP_drawText("Sound title:",6,18);
                    VDP_drawText("                                  ",6,19);
                    VDP_drawText(Sound_Names[S_ID],6,19);//Get sfx title here
                }
            }
            else
            {
                //If neither, clear the lines
                VDP_drawText("                                  ",6,18);
                VDP_drawText("                                  ",6,19);
            }
        }
    }
}

//Processes Credits screen
void Credits()
{
    JOY_setEventHandler( &BtnNada );    //Set Event handler to nothing
    const u8 x=1;       //Constant column value for text disp
    u8 y=1;             //Variable row ~
    const wait=3000;    //Time in MS to wait

    echo_play_bgm(BGM_14);  //Play IceHockey2
    DrawBG(0);              //cls
    DrawBG(10);             //Draw Hockey rink

    //Setup text planes and colors
    VDP_setTextPlan(PLAN_B);
    VDP_setTextPriority(PTRUE);
    VDP_setPaletteColor((OBJPAL * 16)+15,0xEE);   //Yellow
    VDP_setTextPalette(OBJPAL);

    //Draw a line, increment row, draw next line, repeat in screen chunks

    //            1234567890123456789012345678901234567
    VDP_drawText("+-----------------------------------+",x,y);y++;
    VDP_drawText("| ULTRA AIR HOCKEY (Genesis), V1.0  |",x,y);y++;
    VDP_drawText("|              Credits              |",x,y);y++;
    VDP_drawText("+-----------------------------------+",x,y);y++;
    VDP_drawText("|Producer                     Tamkis|",x,y);y++;
    VDP_drawText("|Art creator                  Tamkis|",x,y);y++;
    VDP_drawText("+-----------------------------------+",x,y);y++;
    VDP_drawText("|                                   |",x,y);y++;
    VDP_drawText("|                Music              |",x,y);y++;
    VDP_drawText("|All songs were converted to the    |",x,y);y++;
    VDP_drawText("|Echo sound engine                  |",x,y);y++;
    VDP_drawText("|                                   |",x,y);y++;
    VDP_drawText("|      Various module music artists |",x,y);y++;
    VDP_drawText("|Unless otherwise noted, all modules|",x,y);y++;
    VDP_drawText("|are from modarchive.org/           |",x,y);y++;
    VDP_drawText("|                                   |",x,y);y++;
    VDP_drawText("|http://modarchive.org/index.php?req|",x,y);y++;
    VDP_drawText("|uest=view_by_moduleid&query=NUMBER |",x,y);y++;
    VDP_drawText("v                                   v",x,y);y++;

    //wait MS, clear the text plane, repeat for next screen chunk
    waitMs(wait);
    VDP_clearPlan(BPLAN,0);
    y=1;

    VDP_drawText("|                                   |",x,y);y++;
    VDP_drawText("|hockey_fever.xm  The Einstein Crew |",x,y);y++;
    VDP_drawText("|144817                             |",x,y);y++;
    VDP_drawText("|                                   |",x,y);y++;
    VDP_drawText("|nes_mes2.mod        Goto80         |",x,y);y++;
    VDP_drawText("|                                   |",x,y);y++;
    VDP_drawText("|PITTITLE.mod        (Unknown)      |",x,y);y++;
    VDP_drawText("|112082                             |",x,y);y++;
    VDP_drawText("|                                   |",x,y);y++;
    VDP_drawText("|ice-hockey_94theme.mod Subtance/   |",x,y);y++;
    VDP_drawText("|inflow 121145                      |",x,y);y++;
    VDP_drawText("|                                   |",x,y);y++;
    VDP_drawText("|organmaster.mod     Gamma7         |",x,y);y++;
    VDP_drawText("|169287                             |",x,y);y++;
    VDP_drawText("|                                   |",x,y);y++;
    VDP_drawText("|intro101.mod        w.o.t.w of     |",x,y);y++;
    VDP_drawText("|supplex                            |",x,y);y++;
    VDP_drawText("|                                   |",x,y);y++;
    VDP_drawText("|hurry_up.mod        reflex/rebels  |",x,y);y++;
    VDP_drawText("|                                   |",x,y);y++;
    VDP_drawText("v                                   v",x,y);y++;

    waitMs(wait);
    VDP_clearPlan(BPLAN,0);
    y=1;

    VDP_drawText("|slowmotion.mod     tobbx/Tobbe Lars|",x,y);y++;
    VDP_drawText("|157022                             |",x,y);y++;
    VDP_drawText("|                                   |",x,y);y++;
    VDP_drawText("|Castle_load.mod     Exodus         |",x,y);y++;
    VDP_drawText("|                                   |",x,y);y++;
    VDP_drawText("|complexity.mod      (Unknown)      |",x,y);y++;
    VDP_drawText("|92979                              |",x,y);y++;
    VDP_drawText("|                                   |",x,y);y++;
    VDP_drawText("|Reflexity_music.mod (subsong #3)   |",x,y);y++;
    VDP_drawText("|Unknown             109459         |",x,y);y++;
    VDP_drawText("|                                   |",x,y);y++;
    VDP_drawText("|chipmunks.mod       Jester/Sanity  |",x,y);y++;
    VDP_drawText("|36792                              |",x,y);y++;
    VDP_drawText("|                                   |",x,y);y++;
    VDP_drawText("|icehockey2.mod      Subversion     |",x,y);y++;
    VDP_drawText("|123683                             |",x,y);y++;
    VDP_drawText("+-----------------------------------+",x,y);y++;
    VDP_drawText("v                                   v",x,y);y++;

    waitMs(wait);
    VDP_clearPlan(BPLAN,0);
    y=1;

    VDP_drawText("|             Sound effects         |",x,y);y++;
    VDP_drawText("|Unless otherwise noted, all sfx are|",x,y);y++;
    VDP_drawText("|from Freesound.org                 |",x,y);y++;
    VDP_drawText("|http://www.freesound.org/people/   |",x,y);y++;
    VDP_drawText("|                                   |",x,y);y++;
    VDP_drawText("|ID(+16) Name            URL        |",x,y);y++;
    VDP_drawText("|01      Menu highlight             |",x,y);y++;
    VDP_drawText("|broumbroum/sounds/50561/           |",x,y);y++;
    VDP_drawText("|                                   |",x,y);y++;
    VDP_drawText("|02      Menu select                |",x,y);y++;
    VDP_drawText("|Bertrof/sounds/131658/             |",x,y);y++;
    VDP_drawText("|                                   |",x,y);y++;
    VDP_drawText("|03      Puck hit                   |",x,y);y++;
    VDP_drawText("|krb21/sounds/118604/               |",x,y);y++;
    VDP_drawText("|                                   |",x,y);y++;
    VDP_drawText("|04/30   Puck deflect               |",x,y);y++;
    VDP_drawText("|BranRainey/sounds/108737/          |",x,y);y++;
    VDP_drawText("|                                   |",x,y);y++;
    VDP_drawText("v                                   v",x,y);y++;

    waitMs(wait);
    VDP_clearPlan(BPLAN,0);
    y=1;

    VDP_drawText("|05      Bumper hit                 |",x,y);y++;
    VDP_drawText("|timgormly/sounds/170140/           |",x,y);y++;
    VDP_drawText("|                                   |",x,y);y++;
    VDP_drawText("|06      Powerup get                |",x,y);y++;
    VDP_drawText("|RandomationPictures/sounds/138491/ |",x,y);y++;
    VDP_drawText("|                                   |",x,y);y++;
    VDP_drawText("|07      Powerup use                |",x,y);y++;
    VDP_drawText("|jobro/sounds/35464/                |",x,y);y++;
    VDP_drawText("|                                   |",x,y);y++;
    VDP_drawText("|08      Goal siren                 |",x,y);y++;
    VDP_drawText("|UncleSigmund/sounds/117122/        |",x,y);y++;
    VDP_drawText("|                                   |",x,y);y++;
    VDP_drawText("|09-29   Announcer guy stuff        |",x,y);y++;
    VDP_drawText("|All generated w Acapela Box using  |",x,y);y++;
    VDP_drawText("|the English (UK) Peter voice       |",x,y);y++;
    VDP_drawText("|https://acapela-box.com/AcaBox/    |",x,y);y++;
    VDP_drawText("|index.php                          |",x,y);y++;
    VDP_drawText("|                                   |",x,y);y++;
    VDP_drawText("v                                   v",x,y);y++;

    waitMs(wait);
    VDP_clearPlan(BPLAN,0);
    y=1;

    VDP_drawText("|31      Buzzer                     |",x,y);y++;
    VDP_drawText("|cognito%20perceptu/sounds/17468/   |",x,y);y++;
    VDP_drawText("+-----------------------------------+",x,y);y++;
    VDP_drawText("|             Beta testers          |",x,y);y++;
    VDP_drawText("|                                   |",x,y);y++;
    VDP_drawText("|DUDE #1    - Stuff                 |",x,y);y++;
    VDP_drawText("|DUDE #2    - Stuff                 |",x,y);y++;
    VDP_drawText("|DUDE #3    - Stuff                 |",x,y);y++;
    VDP_drawText("+-----------------------------------+",x,y);y++;
    VDP_drawText("|                                   |",x,y);y++;
    VDP_drawText("|            Special Thanks         |",x,y);y++;
    VDP_drawText("|Oerg866 and SiktheHedgehog         |",x,y);y++;
    VDP_drawText("|Echo Sound Engine and related tools|",x,y);y++;
    VDP_drawText("|                                   |",x,y);y++;
    VDP_drawText("|Stephane              Help, SGDK   |",x,y);y++;
    VDP_drawText("|Nemesis  Exodus emulator (debuging)|",x,y);y++;
    VDP_drawText("v                                   v",x,y);y++;

    waitMs(wait);
    VDP_clearPlan(BPLAN,0);
    y=1;

    VDP_drawText("|                                   |",x,y);y++;
    VDP_drawText("|                                   |",x,y);y++;
    VDP_drawText("|                                   |",x,y);y++;
    VDP_drawText("|                                   |",x,y);y++;
    VDP_drawText("|                                   |",x,y);y++;
    VDP_drawText("|                                   |",x,y);y++;
    VDP_drawText("+===================================+",x,y);y++;
    VDP_drawText("|                YOU                |",x,y);y++;
    VDP_drawText("|            FOR PLAYING!           |",x,y);y++;
    VDP_drawText("|  Ultra Air Hockey (Genesis) V1.0  |",x,y);y++;
    VDP_drawText("|        EagleSoft Ltd 2015         |",x,y);y++;
    VDP_drawText("|       www.eaglesoftltd.com        |",x,y);y++;
    VDP_drawText("+===================================+",x,y);y++;
    VDP_drawText("|                                   |",x,y);y++;
    VDP_drawText("|                                   |",x,y);y++;
    VDP_drawText("|                                   |",x,y);y++;
    VDP_drawText("|                                   |",x,y);y++;
    VDP_drawText("|                                   |",x,y);y++;
    VDP_drawText("|                                   |",x,y);y++;

    waitMs(wait);
    echo_wait_sfx(SFX_02);      //Play select sfx
    VDP_fadeOutAll(100,_FALSE);
    DrawBG(0);                  //cls
}
