#include <Genesis.h>
#include "../res/Gfx/Sprites.h"
#include <memory.h>
#include <tools.h>
#include <timer.h>
#include <vdp_pal.h>
#include <vdp.h>
#include <joy.h>

//Function protos
void InitGame(u8 act);
void Announcer();
void HUD();
void Paused();
void BtnPaused(u16 joy, u16 changed, u16 state);
