vgi2eif.exe "Src\03.vgi" "03.eif"
vgi2eif.exe "Src\07.vgi" "07.eif"
vgi2eif.exe "Src\08.vgi" "08.eif"
vgi2eif.exe "Src\09.vgi" "09.eif"
vgi2eif.exe "Src\10.vgi" "10.eif"

riffstrip.exe "Src\01.wav"
riffstrip.exe "Src\02.wav"
riffstrip.exe "Src\04.wav"
riffstrip.exe "Src\05.wav"
riffstrip.exe "Src\06.wav"

pcm2ewf.exe "Src\01.wav.stripped" "01.ewf"
pcm2ewf.exe "Src\02.wav.stripped" "02.ewf"
pcm2ewf.exe "Src\04.wav.stripped" "04.ewf"
pcm2ewf.exe "Src\05.wav.stripped" "05.ewf"
pcm2ewf.exe "Src\06.wav.stripped" "06.ewf"

del "Src\01.wav.stripped"
del "Src\02.wav.stripped"
del "Src\04.wav.stripped"
del "Src\05.wav.stripped"
del "Src\06.wav.stripped"

xm2esf.exe "Complexity.xif" "Complexity.esf"
rmdir /S /Q "TEMP"

XCopy /Y "03.eif" "../../../fm/11_01.eif"
XCopy /Y "07.eif" "../../../fm/11_02.eif"
XCopy /Y "08.eif" "../../../fm/11_03.eif"
XCopy /Y "09.eif" "../../../fm/11_04.eif"
XCopy /Y "10.eif" "../../../fm/11_05.eif"

XCopy /Y "01.ewf" "../../../dac/11_01.ewf"
XCopy /Y "02.ewf" "../../../dac/11_02.ewf"
XCopy /Y "04.ewf" "../../../dac/11_03.ewf"
XCopy /Y "05.ewf" "../../../dac/11_04.ewf"
XCopy /Y "06.ewf" "../../../dac/11_05.ewf"

XCopy /Y "Complexity.esf" "../../m_Complexity.esf"

del "03.eif"
del "07.eif"
del "08.eif"
del "09.eif"
del "10.eif"

del "01.ewf"
del "02.ewf"
del "04.ewf"
del "05.ewf"
del "06.ewf"

del "Complexity.esf"

Pause