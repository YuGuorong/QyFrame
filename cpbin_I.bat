copy i:\QinYiApp\Settting\profile.bin .\  /y
copy .\O\appsentry.bin I:\QinYiApp\Program\appsentry.bin /y
call release.bat
ResignBin.exe version.txt profile.bin
copy profile.bin i:\QinYiApp\Settting\profile.bin /y
pause