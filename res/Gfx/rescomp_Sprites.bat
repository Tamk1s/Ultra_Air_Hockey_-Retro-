ECHO PLEASE copy the #DEFINEs from the Sprites.h.bak file after running this script!
Pause

rescomp.exe Sprites.res
Move /Y "Sprites.s" "../../src/"
Pause