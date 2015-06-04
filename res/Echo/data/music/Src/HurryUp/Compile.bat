vgi2eif.exe "Src/05.vgi" "05.eif"
vgi2eif.exe "Src/06.vgi" "06.eif"
vgi2eif.exe "Src/07.vgi" "07.eif"
vgi2eif.exe "Src/08.vgi" "08.eif"

riffstrip.exe "Src/01.wav"
riffstrip.exe "Src/02.wav"
riffstrip.exe "Src/03.wav"
riffstrip.exe "Src/04.wav"

pcm2ewf.exe "Src/01.wav.stripped" "01.ewf"
pcm2ewf.exe "Src/02.wav.stripped" "02.ewf"
pcm2ewf.exe "Src/03.wav.stripped" "03.ewf"
pcm2ewf.exe "Src/04.wav.stripped" "04.ewf"

del "Src/01.wav.stripped"
del "Src/02.wav.stripped"
del "Src/03.wav.stripped"
del "Src/04.wav.stripped"

xm2esf "Hurry_up.xif" "Hurry_up.esf"
rmdir /S /Q "TEMP"

XCopy /Y "05.eif" "../../../fm/8_01.eif"
XCopy /Y "06.eif" "../../../fm/8_02.eif"
XCopy /Y "07.eif" "../../../fm/8_03.eif"
XCopy /Y "08.eif" "../../../fm/8_04.eif"

XCopy /Y "01.ewf" "../../../dac/8_01.ewf"
XCopy /Y "02.ewf" "../../../dac/8_02.ewf"
XCopy /Y "03.ewf" "../../../dac/8_03.ewf"
XCopy /Y "04.ewf" "../../../dac/8_04.ewf"

XCopy /Y "Hurry_up.esf" "../../m_Hurryup.esf"

del "05.eif"
del "06.eif"
del "07.eif"
del "08.eif"

del "01.ewf"
del "02.ewf"
del "03.ewf"
del "04.ewf"

del "Hurry_up.esf"

Pause