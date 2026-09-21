@echo off
chcp 65001 > nul
title [UIT - SS004] Game Tetris Console - Nhom Hidden Gem
echo ========================================================
echo   TRƯỜNG ĐH CÔNG NGHỆ THÔNG TIN - ĐHQG TP.HCM (UIT)
echo   ĐỒ ÁN MÔN HỌC: KỸ NĂNG NGHỀ NGHIỆP (SS004) - NHÓM HIDDEN GEM
echo ========================================================
if "%1"=="test" (
    echo Đang biên dịch và chạy Unit Test cho DropSpeedController...
    g++ test_speed.cpp -o test_speed.exe -O2
    if %ERRORLEVEL% NEQ 0 (
        echo [LỖI] Biên dịch test thất bại!
        pause
        exit /b 1
    )
    test_speed.exe
    pause
    exit /b 0
)

echo Đang biên dịch Tetris C++...
rem Danh sach file nguon cua game. Them file .cpp moi vao day khi tach lop.
rem Khong dung *.cpp vi test_speed.cpp co ham main() rieng.
set SRC=main.cpp Blocks.cpp BlockTypes.cpp Board.cpp Bag7.cpp
g++ %SRC% -o Tetris.exe -O2
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
