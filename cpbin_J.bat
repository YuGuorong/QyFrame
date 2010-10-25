copy j:\QinYiApp\Settting\profile.bin .\  /y
copy .\O\appsentry.bin j:\QinYiApp\Program\appsentry.bin /y
call release.bat
ResignBin.exe version.txt profile.bin
copy profile.bin j:\QinYiApp\Settting\profile.bin /y
pause