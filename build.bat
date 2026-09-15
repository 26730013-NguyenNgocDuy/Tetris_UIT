@echo off
rem ============================================================
rem  Bien dich Tetris Console.  Can g++ (MinGW / Code::Blocks) hoac clang++.
rem  Cach dung:  build        -> bien dich
rem              build run    -> bien dich xong chay luon
rem ============================================================
cd /d "%~dp0"

where g++ >nul 2>nul
if not errorlevel 1 goto dung_gpp

where clang++ >nul 2>nul
if not errorlevel 1 goto dung_clang

echo [LOI] Khong tim thay g++ hoac clang++ trong PATH.
echo       Neu da cai Code::Blocks, them "C:\Program Files\CodeBlocks\MinGW\bin" vao PATH.
exit /b 1

:dung_gpp
echo Bien dich bang g++ ...
g++ -std=c++14 -Wall -Wextra -O2 src\*.cpp -o tetris.exe
goto ket_qua

:dung_clang
echo Bien dich bang clang++ ...
clang++ -std=c++14 -Wall -Wextra -O2 src\*.cpp -o tetris.exe -luser32
goto ket_qua

:ket_qua
if errorlevel 1 (
    echo [LOI] Bien dich that bai.
    exit /b 1
)
echo Xong: tetris.exe
if /i "%~1"=="run" tetris.exe
