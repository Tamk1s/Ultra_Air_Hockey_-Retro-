vgi2eif.exe "Src/01.vgi" "01.eif"
vgi2eif.exe "Src/02.vgi" "02.eif"
vgi2eif.exe "Src/03.vgi" "03.eif"

xm2esf.exe "Castle_Load.xif" "Castle_Load.esf"
rmdir /S /Q "TEMP"

XCopy /Y "01.eif" "../../../fm/10_01.eif"
XCopy /Y "02.eif" "../../../fm/10_02.eif"
XCopy /Y "03.eif" "../../../fm/10_03.eif"

XCopy /Y "Castle_Load.xif" "../../m_CastleLoad.esf"

del "01.eif"
del "02.eif"
del "03.eif"

del "Castle_Load.esf"
Pause