#include "../inc/DrawBG.h"

//Routine draws all game BGs and FGs as appropriately via ID
//ID 0=pseudo cls routine
void DrawBG(u8 ID)
{
    /*
    u16 pal=
    {
        0x8728, 0x005C, 0x00C4, 0x005C, 0x4746, 0x68D4, 0xBEB4, 0x0000,
        0x8728, 0x005C, 0x00C4, 0x005C, 0x2073, 0x7828, 0x3638, 0x5C29
    };
    */


    ind = TILE_USERINDEX;
    switch (ID)
    {
        case 0:
            //Cls
            VDP_resetScreen();                          //Reset VRAM
            VDP_setPaletteColors(0, palette_black, 64); //reset all palette to black
            VDP_fillTileData(0x00, ind, 1295, FALSE);   //Clear all tiles
            for (ind=0;ind<=28;ind++)                   //Clear all text lines
            {
                 VDP_clearTextLine(ind);
            }
            break;
        case 1:
            VDP_drawImageEx(APLAN, &S1, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, ind), 0, 0, TRUE, FALSE);
            break;
        case 2:
            VDP_drawImageEx(APLAN, &S2, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, ind), 0, 0, TRUE, FALSE);
            break;
        case 3:
            VDP_drawImageEx(APLAN, &S3, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, ind), 0, 0, TRUE, FALSE);
            break;
        case 4:
            VDP_drawImageEx(APLAN, &S4, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, ind), 0, 0, TRUE, FALSE);
            break;
        case 5:
            VDP_drawImageEx(APLAN, &S5, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, ind), 0, 0, TRUE, FALSE);
            break;
        case 6:
            VDP_drawImageEx(APLAN, &S6, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, ind), 0, 0, TRUE, FALSE);
            break;
        case 7:
            VDP_drawImageEx(APLAN, &S7, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, ind), 0, 0, TRUE, FALSE);
            break;
        case 8:
            //VDP_setPalette(PAL0, pal);
            VDP_drawImageEx(APLAN, &S8, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, ind), 0, 0, TRUE, FALSE);
            break;
        case 9:
            VDP_drawImageEx(APLAN, &S9, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, ind), 0, 0, TRUE, FALSE);
            break;
        case 10:
            VDP_drawImageEx(APLAN, &S10, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, ind), 0, 0, TRUE, FALSE);
            break;
        case 11:
            VDP_drawImageEx(APLAN, &M1, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, ind), 0, 0, TRUE, FALSE);
            break;
        case 12:
            VDP_drawImageEx(APLAN, &M2, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, ind), 0, 0, TRUE, FALSE);
            break;
        case 13:
            VDP_drawImageEx(APLAN, &M3, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, ind), 0, 0, TRUE, FALSE);
            break;
        case 14:
            VDP_drawImageEx(APLAN, &B1, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, ind), 0, 0, TRUE, FALSE);
            break;
        case 15:
            VDP_drawImageEx(APLAN, &B2, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, ind), 0, 0, TRUE, FALSE);
            break;
        case 16:
            VDP_drawImageEx(APLAN, &B3, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, ind), 0, 0, TRUE, FALSE);
            break;
        case 17:
            VDP_drawImageEx(APLAN, &B4, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, ind), 0, 0, TRUE, FALSE);
            break;
        case 18:
            VDP_drawImageEx(APLAN, &FMV_BG, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, ind), 0, 0, TRUE, FALSE);
            break;
        case 19:
            ind +=FMV_BG.tileset->numTile;
            VDP_drawImageEx(BPLAN, &FMV_Text, TILE_ATTR_FULL(PAL1, TRUE, FALSE, FALSE, ind), 0, 0, TRUE, FALSE);
            break;
        case 20:
            VDP_drawImageEx(APLAN, &FMV_Ani, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, ind), 0, 0, TRUE, FALSE);
            break;
    }
}
