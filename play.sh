#!/bin/bash
# Biên dịch và chạy Tetris_UIT trên macOS / Linux
cd "$(dirname "$0")" || exit 1

echo "Đang biên dịch Tetris C++..."
# Ma nguon nam trong src/ chia theo vai tro: core (luat choi), game (dieu khien), ui (hien thi).
# Them lop moi chi can dat file .cpp vao dung thu muc, khong phai sua script nay.
INC="-Isrc/core -Isrc/game -Isrc/ui"
SRC="src/*.cpp src/core/*.cpp src/game/*.cpp src/ui/*.cpp"

if ! g++ -std=c++11 -O2 $INC $SRC -o tetris; then
    echo "[LỖI] Không thể biên dịch. Hãy cài Xcode Command Line Tools: xcode-select --install"
    exit 1
fi

echo "[OK] Biên dịch thành công! Đang khởi động trò chơi..."
./tetris
echo
echo "Cảm ơn bạn đã trải nghiệm Tetris_UIT!"
