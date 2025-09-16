@echo off
REM Script para compilar e rodar o teste da CPU

mkdir build 2>nul
mkdir bin 2>nul

cl /I include /Fo"build\cpu.obj" /c src\cpu.c
cl /I include /Fo"build\test_cpu.obj" /c src\test_cpu.c
cl /Fe"bin\test_cpu.exe" build\cpu.obj build\test_cpu.obj /link advapi32.lib

echo Running test_cpu...
bin\test_cpu.exe

pause
