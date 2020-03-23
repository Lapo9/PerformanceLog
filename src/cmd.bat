rmdir obj /S /Q
cl /EHsc /experimental:module /std:c++latest timer.ixx session.ixx formatters\measurementOutputFormat.ixx formatters\chromeTracingFormat.ixx performanceLog.ixx MainTest.cpp /link /out:executable.exe
md obj
move *.obj obj
move *.ifc obj
move *.exe obj