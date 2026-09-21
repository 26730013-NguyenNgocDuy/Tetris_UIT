#!/bin/bash
# Biên dịch và chạy Tetris_UIT trên macOS / Linux
cd "$(dirname "$0")" || exit 1

echo "Đang biên dịch Tetris C++..."
if ! g++ -std=c++11 -O2 main.cpp -o tetris; then
    echo "[LỖI] Không thể biên dịch. Hãy cài Xcode Command Line Tools: xcode-select --install"
    exit 1
fi

echo "[OK] Biên dịch thành công! Đang khởi động trò chơi..."
./tetris
echo
echo "Cảm ơn bạn đã trải nghiệm Tetris_UIT!"
