REM Script builds the PCM EWF files
REM It strips all of the wav files raw,
REM and converts the raw files to EWF,
REM and lastly deletes the temporary .stripped raw files

riffstrip.exe Src/Siren.wav
riffstrip.exe Src/v1.wav
riffstrip.exe Src/v2.wav
riffstrip.exe Src/v3.wav
riffstrip.exe Src/v4.wav
riffstrip.exe Src/v5.wav
riffstrip.exe Src/v6.wav
riffstrip.exe Src/v7.wav
riffstrip.exe Src/v8.wav
riffstrip.exe Src/v9.wav
riffstrip.exe Src/v10.wav
riffstrip.exe Src/vBlue.wav
riffstrip.exe Src/vCredits.wav
riffstrip.exe Src/vGameover.wav
riffstrip.exe Src/vGoal.wav
riffstrip.exe Src/vOptions.wav
riffstrip.exe Src/vPlay.wav
riffstrip.exe Src/vPlayers.wav
riffstrip.exe Src/vRed.wav
riffstrip.exe Src/vto.wav
riffstrip.exe Src/vUAH.wav
riffstrip.exe Src/vWins.wav
riffstrip.exe Src/Bumper.wav
riffstrip.exe Src/Buzzer.wav
riffstrip.exe Src/Deflect.wav
riffstrip.exe Src/DeflectS.wav
riffstrip.exe Src/EagleSoft.wav
riffstrip.exe Src/HiLite.wav
riffstrip.exe Src/Hit.wav
riffstrip.exe Src/PwrGet.wav
riffstrip.exe Src/PwrUse.wav
riffstrip.exe Src/Select.wav

pcm2ewf.exe Src/Siren.wav.stripped s_Siren.ewf
pcm2ewf.exe Src/v1.wav.stripped s_v1.ewf
pcm2ewf.exe Src/v2.wav.stripped s_v2.ewf
pcm2ewf.exe Src/v3.wav.stripped s_v3.ewf
pcm2ewf.exe Src/v4.wav.stripped s_v4.ewf
pcm2ewf.exe Src/v5.wav.stripped s_v5.ewf
pcm2ewf.exe Src/v6.wav.stripped s_v6.ewf
pcm2ewf.exe Src/v7.wav.stripped s_v7.ewf
pcm2ewf.exe Src/v8.wav.stripped s_v8.ewf
pcm2ewf.exe Src/v9.wav.stripped s_v9.ewf
pcm2ewf.exe Src/v10.wav.stripped s_v10.ewf
pcm2ewf.exe Src/vBlue.wav.stripped s_vBlue.ewf
pcm2ewf.exe Src/vCredits.wav.stripped s_vCredits.ewf
pcm2ewf.exe Src/vGameover.wav.stripped s_vGameover.ewf
pcm2ewf.exe Src/vGoal.wav.stripped s_vGoal.ewf
pcm2ewf.exe Src/vOptions.wav.stripped s_vOptions.ewf
pcm2ewf.exe Src/vPlay.wav.stripped s_vPlay.ewf
pcm2ewf.exe Src/vPlayers.wav.stripped s_vPlayers.ewf
pcm2ewf.exe Src/vRed.wav.stripped s_vRed.ewf
pcm2ewf.exe Src/vto.wav.stripped s_vto.ewf
pcm2ewf.exe Src/vUAH.wav.stripped s_vUAH.ewf
pcm2ewf.exe Src/vWins.wav.stripped s_vWins.ewf
pcm2ewf.exe Src/Bumper.wav.stripped s_Bumper.ewf
pcm2ewf.exe Src/Buzzer.wav.stripped s_Buzzer.ewf
pcm2ewf.exe Src/Deflect.wav.stripped s_Deflect.ewf
pcm2ewf.exe Src/DeflectS.wav.stripped s_DeflectS.ewf
pcm2ewf.exe Src/EagleSoft.wav.stripped s_EagleSoft.ewf
pcm2ewf.exe Src/HiLite.wav.stripped s_HiLite.ewf
pcm2ewf.exe Src/Hit.wav.stripped s_Hit.ewf
pcm2ewf.exe Src/PwrGet.wav.stripped s_PwrGet.ewf
pcm2ewf.exe Src/PwrUse.wav.stripped s_PwrUse.ewf
pcm2ewf.exe Src/Select.wav.stripped s_Select.ewf

del "Src\Siren.wav.stripped"
del "Src\v1.wav.stripped"
del "Src\v2.wav.stripped"
del "Src\v3.wav.stripped"
del "Src\v4.wav.stripped"
del "Src\v5.wav.stripped"
del "Src\v6.wav.stripped"
del "Src\v7.wav.stripped"
del "Src\v8.wav.stripped"
del "Src\v9.wav.stripped"
del "Src\v10.wav.stripped"
del "Src\vBlue.wav.stripped"
del "Src\vCredits.wav.stripped"
del "Src\vGameover.wav.stripped"
del "Src\vGoal.wav.stripped"
del "Src\vOptions.wav.stripped"
del "Src\vPlay.wav.stripped"
del "Src\vPlayers.wav.stripped"
del "Src\vRed.wav.stripped"
del "Src\vto.wav.stripped"
del "Src\vUAH.wav.stripped"
del "Src\vWins.wav.stripped"
del "Src\Bumper.wav.stripped"
del "Src\Buzzer.wav.stripped"
del "Src\Deflect.wav.stripped"
del "Src\DeflectS.wav.stripped"
del "Src\EagleSoft.wav.stripped"
del "Src\HiLite.wav.stripped"
del "Src\Hit.wav.stripped"
del "Src\PwrGet.wav.stripped"
del "Src\PwrUse.wav.stripped"
del "Src\Select.wav.stripped"
Pause