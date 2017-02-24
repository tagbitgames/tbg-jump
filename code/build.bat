@echo off
call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" x86

set ProjectName=jump
set BinaryFileName=%ProjectName%32d

set CommonCompilerFlags=-Od -MTd -nologo -fp:fast -fp:except- -Gm- -GR- -EHsc -EHa- -Zo -Oi -Z7 -WX -W4 
set CommonCompilerFlags=-wd4100 -wd4189 -wd4201 -wd4244 -wd4459 -wd4505 %CommonCompilerFlags%
set CommonCompilerFlags=-DUNICODE=1 -DRELEASE_MODE=0 -DPLATFORM_WINDOWS=1 %CommonCompilerFlags%
set CommonLinkerFlags=-incremental:no -opt:ref user32.lib ws2_32.lib

IF NOT EXIST ..\build\ mkdir ..\build\
pushd ..\build\

del *.pdb > NUL 2> NUL

cl %CommonCompilerFlags% ..\code\win32_main.cpp /link %CommonLinkerFlags% /out:%BinaryFileName%.exe

popd