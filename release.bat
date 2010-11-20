QYReleaseTool.exe ./o/AppsEntry.map ./o/AppsEntry.bin -name>.\version.txt
copy .\version.txt o\version.txt /y
winrar.exe ./Release.rar ./o/AppsEntry.bin  ./o/version.txt
pause