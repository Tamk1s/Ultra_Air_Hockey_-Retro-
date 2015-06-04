vgi2eif.exe "Src\01.vgi" "01.eif"
vgi2eif.exe "Src\02.vgi" "02.eif"
vgi2eif.exe "Src\03.vgi" "03.eif"
vgi2eif.exe "Src\04.vgi" "04.eif"
xm2esf.exe "nes_mes2.xif" "nes_mes2.esf"
rmdir /S /Q "TEMP"

XCopy /Y "01.eif" "../../../fm/3_01.eif"
XCopy /Y "02.eif" "../../../fm/3_02.eif"
XCopy /Y "03.eif" "../../../fm/3_03.eif"
XCopy /Y "04.eif" "../../../fm/3_04.eif"
XCopy /Y "nes_mes2.esf" "../../m_nes_mes2.esf"

del "01.eif"
del "02.eif"
del "03.eif"
del "04.eif"
del "nes_mes2.esf"

Pause