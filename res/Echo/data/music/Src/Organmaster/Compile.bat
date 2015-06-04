vgi2eif.exe "Src\03.vgi" "03.eif"
vgi2eif.exe "Src\04.vgi" "04.eif"
vgi2eif.exe "Src\05.vgi" "05.eif"
vgi2eif.exe "Src\06.vgi" "06.eif"
vgi2eif.exe "Src\07.vgi" "07.eif"
vgi2eif.exe "Src\08.vgi" "08.eif"
vgi2eif.exe "Src\09.vgi" "09.eif"
vgi2eif.exe "Src\10.vgi" "10.eif"
vgi2eif.exe "Src\11.vgi" "11.eif"
vgi2eif.exe "Src\12.vgi" "12.eif"

riffstrip.exe "Src\01.wav"
riffstrip.exe "Src\02.wav"

pcm2ewf.exe "src\01.wav.stripped" "01.ewf"
pcm2ewf.exe "src\02.wav.stripped" "02.ewf"

del "src\01.wav.stripped"
del "src\02.wav.stripped"

xm2esf.exe "Organmaster.xif" "Organmaster.esf"
rmdir /S /Q "TEMP"

XCopy /Y "03.eif" "../../../fm/6_01.eif"
XCopy /Y "04.eif" "../../../fm/6_02.eif"
XCopy /Y "05.eif" "../../../fm/6_03.eif"
XCopy /Y "06.eif" "../../../fm/6_04.eif"
XCopy /Y "07.eif" "../../../fm/6_05.eif"
XCopy /Y "08.eif" "../../../fm/6_06.eif"
XCopy /Y "09.eif" "../../../fm/6_07.eif"
XCopy /Y "10.eif" "../../../fm/6_08.eif"
XCopy /Y "11.eif" "../../../fm/6_09.eif"
XCopy /Y "12.eif" "../../../fm/6_10.eif"

XCopy /Y "01.ewf" "../../../dac/6_01.ewf"
XCopy /Y "02.ewf" "../../../dac/6_02.ewf"

XCopy /Y "Organmaster.esf" "../../m_Organmaster.esf"

del "03.eif"
del "04.eif"
del "05.eif"
del "06.eif"
del "07.eif"
del "08.eif"
del "09.eif"
del "10.eif"
del "11.eif"
del "12.eif"

del "01.ewf"
del "02.ewf"

del "Organmaster.esf"

Pause