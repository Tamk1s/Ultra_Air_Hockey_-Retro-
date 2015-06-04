REM Script using Rescomp on musres.res,
REM generates a .h file,
REM and then moves the .s file where it belongs
rescomp.exe Musres.res
Move /Y Musres.s ../../../src/
Pause