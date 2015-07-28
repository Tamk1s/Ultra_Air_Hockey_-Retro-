#include <Genesis.h>
#include <timer.h>
//#include <sprite_eng.h>
#include "../inc/main.h"
#include "../res/Gfx/Planes.h"
#include "../res/Gfx/Sprites.h"
#include <vdp_pal.h>
#include <joy.h>

u8 Skip=_FALSE;     //Flag if skipping something

//Function protos
void FMV();
void Title();
void BtnSkip(u16 joy, u16 changed, u16 state);
