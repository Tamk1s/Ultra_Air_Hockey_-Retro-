vgi2eif.exe "Src\04.vgi" "04.eif"
vgi2eif.exe "Src\05.vgi" "05.eif"
vgi2eif.exe "Src\06.vgi" "06.eif"
vgi2eif.exe "Src\07.vgi" "07.eif"
vgi2eif.exe "Src\08.vgi" "08.eif"
vgi2eif.exe "Src\09.vgi" "09.eif"
vgi2eif.exe "Src\10.vgi" "10.eif"

riffstrip.exe "Src\01.wav"
riffstrip.exe "Src\02.wav"
riffstrip.exe "Src\03.wav"

pcm2ewf.exe "Src\01.wav.stripped" "01.ewf"
pcm2ewf.exe "Src\02.wav.stripped" "02.ewf"
pcm2ewf.exe "Src\03.wav.stripped" "03.ewf"

del "Src\01.wav.stripped"
del "Src\02.wav.stripped"
del "Src\03.wav.stripped"

xm2esf.exe "Pittitle.xif" "Pittitle.esf"
rmdir /S /Q "TEMP"

XCopy /Y "04.eif" "../../../fm/4_01.eif"
XCopy /Y "05.eif" "../../../fm/4_02.eif"
XCopy /Y "06.eif" "../../../fm/4_03.eif"
XCopy /Y "07.eif" "../../../fm/4_04.eif"
XCopy /Y "08.eif" "../../../fm/4_05.eif"
XCopy /Y "09.eif" "../../../fm/4_06.eif"
XCopy /Y "10.eif" "../../../fm/4_07.eif"

XCopy /Y "01.ewf" "../../../dac/4_01.ewf"
XCopy /Y "02.ewf" "../../../dac/4_02.ewf"
XCopy /Y "03.ewf" "../../../dac/4_03.ewf"

XCopy /Y "Pittitle.esf" "../../m_Pittitle.esf"

del "04.eif"
del "05.eif"
del "06.eif"
del "07.eif"
del "08.eif"
del "09.eif"
del "10.eif"

del "01.ewf"
del "02.ewf"
del "03.ewf"

Pause