rmdir obj /S /Q
cl /EHsc /experimental:module /std:c++latest timer.ixx formatters\measurementOutputFormat.ixx formatters\chromeTracingFormat.ixx session.ixx performanceLog.ixx MainTest.cpp /link /out:executable.exe
md obj
move *.obj obj
move *.ifc obj
move *.exe obj