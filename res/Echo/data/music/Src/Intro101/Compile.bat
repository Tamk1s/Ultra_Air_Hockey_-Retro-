vgi2eif.exe "Src\04.vgi" "04.eif"
vgi2eif.exe "Src\05.vgi" "05.eif"
vgi2eif.exe "Src\06.vgi" "06.eif"

riffstrip.exe "Src\01.wav"
riffstrip.exe "Src\02.wav"
riffstrip.exe "Src\03.wav"

pcm2ewf.exe "Src\01.wav.stripped" "01.ewf"
pcm2ewf.exe "Src\02.wav.stripped" "02.ewf"
pcm2ewf.exe "Src\03.wav.stripped" "03.ewf"

del "Src\01.wav.stripped"
del "Src\02.wav.stripped"
del "Src\03.wav.stripped"

xm2esf "Intro101.xif" "Intro101.esf"
rmdir /S /Q "TEMP"

XCopy /Y "04.eif" "../../../fm/7_01.eif"
XCopy /Y "05.eif" "../../../fm/7_02.eif"
XCopy /Y "06.eif" "../../../fm/7_03.eif"

XCopy /Y "01.ewf" "../../../dac/7_01.ewf"
XCopy /Y "02.ewf" "../../../dac/7_02.ewf"
XCopy /Y "03.ewf" "../../../dac/7_03.ewf"

XCopy /Y "Intro101.esf" "m_Intro101.esf"

del "04.eif"
del "05.eif"
del "06.eif"

del "01.ewf"
del "02.ewf"
del "03.ewf"

del "Intro101.esf"

Pause