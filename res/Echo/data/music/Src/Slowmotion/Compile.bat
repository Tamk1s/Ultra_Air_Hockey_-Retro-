vgi2eif.exe "Src\01.vgi" "01.eif"
vgi2eif.exe "Src\02.vgi" "02.eif"
vgi2eif.exe "Src\03.vgi" "03.eif"
vgi2eif.exe "Src\04.vgi" "04.eif"
vgi2eif.exe "Src\05.vgi" "05.eif"
vgi2eif.exe "Src\06.vgi" "06.eif"
vgi2eif.exe "Src\07.vgi" "07.eif"

xm2esf.exe "Slowmotion.xif" "Slowmotion.esf"
rmdir /S /Q "TEMP"

XCopy /Y "01.eif" "../../../fm/9_01.eif"
XCopy /Y "02.eif" "../../../fm/9_02.eif"
XCopy /Y "03.eif" "../../../fm/9_03.eif"
XCopy /Y "04.eif" "../../../fm/9_04.eif"
XCopy /Y "05.eif" "../../../fm/9_05.eif"
XCopy /Y "06.eif" "../../../fm/9_06.eif"
XCopy /Y "07.eif" "../../../fm/9_07.eif"

XCopy /Y "Slowmotion.esf" "../../m_slowmotion.esf"

del "01.eif"
del "02.eif"
del "03.eif"
del "04.eif"
del "05.eif"
del "06.eif"
del "07.eif"

del "Slowmotion.esf"

Pause