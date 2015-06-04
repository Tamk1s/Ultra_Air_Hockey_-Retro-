vgi2eif.exe "Src\02.vgi" "02.eif"
vgi2eif.exe "Src\03.vgi" "03.eif"
vgi2eif.exe "Src\04.vgi" "04.eif"
vgi2eif.exe "Src\05.vgi" "05.eif"

riffstrip.exe "Src\01.wav"
pcm2ewf.exe "Src\01.wav.stripped" "01.ewf"
del "Src\01.wav.stripped"

xm2esf.exe "Reflexity_music.xif" "Reflexity_music.esf"
rmdir /S /Q "TEMP"

XCopy /Y "02.eif" "../../../fm/12_01.eif"
XCopy /Y "03.eif" "../../../fm/12_02.eif"
XCopy /Y "04.eif" "../../../fm/12_03.eif"
XCopy /Y "05.eif" "../../../fm/12_04.eif"

XCopy /Y "01.ewf" "../../../dac/12_01.ewf"

XCopy /Y "Reflexity_music.esf" "../../m_Reflexity_music.esf"

del "02.eif"
del "03.eif"
del "04.eif"
del "05.eif"

del "01.ewf"

del "Reflexity_music.esf"

Pause