<h1 align="center">🧱 TETRIS_UIT 🧱</h1>

<p align="center">
  <b>Xếp gạch. Phá hàng. Rồi chạy đua với chính tốc độ của bạn.</b><br>
  <i>Tetris chạy ngay trong cửa sổ console, viết bằng C++ thuần, không cần engine hay thư viện nào.</i>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=cplusplus&logoColor=white" alt="C++">
  <img src="https://img.shields.io/badge/Windows-Console-0078D6?style=for-the-badge&logo=windows&logoColor=white" alt="Windows Console">
  <img src="https://img.shields.io/badge/UIT-Hidden%20Gem-ff69b4?style=for-the-badge" alt="UIT Hidden Gem">
</p>

---

```
▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓
▓▓          ██                ▓▓
▓▓          ██                ▓▓      Gạch rơi xuống...
▓▓          ██                ▓▓
▓▓          ██                ▓▓
▓▓                            ▓▓
▓▓                            ▓▓      ...bạn né trái, né phải...
▓▓                            ▓▓
▓▓████                    ████▓▓
▓▓████      ████      ████████▓▓      ...lấp đầy một hàng...
▓▓██████████████████  ████████▓▓
▓▓██████████████████  ████████▓▓      💥 BÙM! Hàng biến mất.
▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓      Và gạch rơi NHANH hơn. 😈
```

**Tetris_UIT** là đồ án môn *Kỹ năng nghề nghiệp* của nhóm **Hidden Gem** tại UIT. Tụi mình code theo kiểu *vibe coding*: code một chút, chơi thử một ván, thua, sửa, chơi lại. Mỗi thành viên phụ trách một mảnh ghép, và game lớn dần qua từng Pull Request.

---

## 🔥 Điều làm game này khác biệt: phá càng nhiều, rơi càng nhanh

Ở đây không có level để bạn "nghỉ mệt". **Mỗi hàng bạn phá là một lần game tăng tốc.**

| Số hàng đã phá | Tốc độ rơi (mỗi ô) | Cảm giác |
| :------------: | :----------------: | -------- |
| 0 | 500 ms | 😌 Thong thả, uống miếng nước |
| 5 | 350 ms | 🙂 Bắt đầu phải tập trung |
| 10 | 200 ms | 😰 Tay bắt đầu run |
| **14+** | **100 ms** | 🤯 Nhanh gấp 5 lần, tốc độ tối đa |

Mỗi hàng phá được làm gạch rơi nhanh thêm **30 ms**. Phá 4 hàng một lúc là tăng tốc 120 ms một phát. Điểm thưởng lớn nhất của game này là… sự sống sót. 😎

---

## ✨ Tính năng hiện có

- 🎮 **Bàn chơi cổ điển**: khung 13 × 18 ô, viền dày, gạch vẽ bằng ký tự khối `█` đậm chất retro.
- 💥 **Phá hàng có hiệu ứng**: hàng đầy sẽ biến mất từng hàng một, mọi thứ phía trên sụp xuống theo.
- ⚡ **Tăng tốc theo tiến độ**: xem bảng phía trên, game không bao giờ để bạn thoải mái lâu.
- 🪶 **Siêu nhẹ**: một file `.cpp`, một file header, biên dịch xong là chơi.

---

## ⌨️ Điều khiển

| Phím | Hành động |
| :--: | --------- |
| `A` | ⬅️ Sang trái |
| `D` | ➡️ Sang phải |
| `X` | ⬇️ Đẩy khối xuống nhanh hơn |
| `Q` | 🚪 Thoát game |

### Xoay khối bằng tính đa hình

`Blocks` là lớp cơ sở trừu tượng, `rotate()` là hàm thuần ảo, mỗi loại khối xoay một kiểu:

| Lớp | Khi xoay |
| --- | --- |
| `BlockO` | Không đổi gì, hình vuông xoay vẫn vậy |
| `BlockI` | Đổi qua lại nằm ngang và dựng đứng, đúng 2 trạng thái |
| `BlockT`, `BlockS`, `BlockZ`, `BlockJ`, `BlockL` | Xoay 90 độ, đủ 4 trạng thái |

Chỗ gọi chỉ cầm con trỏ `Blocks *current` và gọi `current->rotate()`, không cần biết đang là khối gì.

> 💡 Nhớ tắt **Caps Lock** và chuyển bộ gõ sang **tiếng Anh**, không thì game sẽ không nhận phím đâu!

---

## 🚀 Cài đặt và chơi ngay

> 🍎 **macOS / Linux**: chạy `./play.sh` (hoặc `g++ -std=c++11 main.cpp Blocks.cpp BlockTypes.cpp Board.cpp Bag7.cpp -o tetris && ./tetris`). `Platform.h` tự thay `<windows.h>`/`<conio.h>` bằng termios và mã màu ANSI.

**1. Tải source về**

```bash
git clone https://github.com/26730013-NguyenNgocDuy/Tetris_UIT.git
cd Tetris_UIT
```

**2. Biên dịch & Chơi game**

- **🌐 Cách 1: Chơi ngay trên Trình Duyệt Web (Khuyên Dùng khi Báo Cáo / Trình Chiếu)**
  - Nhấp đúp vào **`Play_Web.bat`** hoặc mở trực tiếp [dist_web/index.html](file:///dist_web/index.html).
  - Giao diện Light/Dark sắc nét, chuẩn Canvas 60 FPS, âm thanh Polyphonic Web Audio, hỗ trợ đầy đủ phím và cảm ứng Mobile!

- **🖥️ Cách 2: Chơi bản C++ Console (Minh chứng môn OOP)**
  - Với **MinGW / g++**:
  ```bash
  g++ -O2 main.cpp Blocks.cpp BlockTypes.cpp Board.cpp Bag7.cpp -o tetris.exe
  ./tetris.exe
  ```
  - Hoặc click đúp file **`Play_Game.bat`** để tự động build và chạy ngay trong 1 click!

**3. Chạy kiểm thử tự động (Unit Test)**

Để kiểm thử logic tốc độ rơi, combo và điểm số:

```bash
g++ -O2 test_speed.cpp -o test_speed.exe
./test_speed.exe
```

---

## ⚡ Cơ chế gia tốc & Điểm số (SV5)

- **Tốc độ ban đầu**: `500ms` / bước rơi.
- **Gia tốc**: Mỗi hàng xóa được giảm `25ms`.
- **Cấp độ (Level)**: Tăng 1 cấp mỗi 10 hàng xóa được (`Level = 1 + TotalLines / 10`).
- **Hệ số Combo**: Ăn hàng liên tiếp kích hoạt combo streak nhân điểm thưởng (`(combo - 1) * 50 * level`).
- **Ngưỡng an toàn tối thiểu**: `80ms` (đảm bảo không bị giật lag hay rơi tức thời).

---

## 💡 Bí kíp sống sót

- 🧠 **Chừa một cột trống** sát tường để chờ khối thẳng rồi phá liền 4 hàng. Nhưng nhớ là phá xong thì gạch sẽ rơi nhanh hơn hẳn!
- 🏔️ **Đừng xây núi ở giữa.** Gạch luôn xuất hiện gần giữa bàn, chồng cao ở đó là thua sớm.
- 🐢 **Tận dụng lúc đầu game** để xếp gạch thật phẳng. Đây là lúc duy nhất bạn còn thời gian suy nghĩ.
- 🧘 **Bình tĩnh.** Gạch rơi 80 ms một ô không đáng sợ bằng việc bạn luống cuống bấm nhầm phím.

---

## 📂 Cấu trúc dự án

```
Tetris_UIT/
├── main.cpp                # Vòng lặp game, giao diện, điều khiển
├── Blocks.h / Blocks.cpp   # Lớp trừu tượng cho một khối: hình dạng, vị trí, hàm xoay ảo
├── BlockTypes.h / .cpp     # Bảy lớp con: BlockI, BlockO, BlockT, BlockS, BlockZ, BlockJ, BlockL
├── Board.h / Board.cpp     # Sân chơi: lưới, va chạm, đặt khối, xoá hàng
├── Bag7.h / Bag7.cpp       # Túi 7 khối, phát khối không bị trùng liên tục
├── ColorRenderer.h         # Renderer màu sắc ANSI, bảng mã CP437, khử giật màn hình
├── DropSpeedController.h   # Quản lý tốc độ rơi tăng dần, level và điểm combo (SV5)
├── test_speed.cpp          # Bộ kiểm thử tự động (Unit Test 6/6 test cases)
├── Play_Game.bat           # Launcher 1-click tự động build và chạy
└── README.md
```

---

<p align="center">
  <b>Làm với ❤️ và rất nhiều ván thua bởi nhóm Hidden Gem, UIT</b><br>
  <i>Bạn trụ được bao nhiêu hàng? 👀</i>
</p>
