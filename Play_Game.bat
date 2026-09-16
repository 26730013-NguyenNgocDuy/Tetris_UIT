@echo off
chcp 65001 > nul
title [UIT - SS004] Game Tetris Console
echo ========================================================
echo   TRƯỜNG ĐH CÔNG NGHỆ THÔNG TIN - ĐHQG TP.HCM (UIT)
echo   ĐỒ ÁN MÔN HỌC: KỸ NĂNG NGHỀ NGHIỆP (SS004) - NHÓM HIDDEN GEM
echo ========================================================
echo.
echo Đang biên dịch Tetris C++...
g++ main.cpp -o Tetris.exe -O2
if %ERRORLEVEL% NEQ 0 (
    echo [LỖI] Không thể biên dịch mã nguồn C++. Vui lòng kiểm tra lại g++ (MinGW).
    pause
    exit /b 1
)

echo [OK] Biên dịch thành công! Đang khởi động trò chơi...
cls
Tetris.exe
echo.
echo Cảm ơn bạn đã trải nghiệm Tetris_UIT!
pause
