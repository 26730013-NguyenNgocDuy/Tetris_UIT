# 📋 BÁO CÁO AUDIT TOÀN DIỆN GIT REPOSITORY & KIẾN TRÚC OOP
## DỰ ÁN: TETRIS_UIT — NHÓM HIDDEN GEM (MÔN: KỸ NĂNG NGHỀ NGHIỆP / SS004)

> **Căn cứ pháp lý & Kỹ thuật:** Toàn bộ dữ liệu trong tài liệu này được trích xuất trực tiếp từ Git commit history, Git log graph, GitHub Pull Requests (`gh pr list`), Git diff và mã nguồn thực tế tại repository: `https://github.com/26730013-NguyenNgocDuy/Tetris_UIT.git`.
> **Nguyên tắc:** 100% bằng chứng thực tế từ mã nguồn (SSOT), không suy đoán, không làm đẹp lịch sử.

---

# 1. Repository State (Trạng thái Repository)

- **Remote GitHub URL:** `https://github.com/26730013-NguyenNgocDuy/Tetris_UIT.git`
- **Default / Main Branch:** `main`
- **HEAD hiện tại trên `main`:** Commit `cd492e706581f40d7c3b3719cf31dc566cfe87d6` (*Merge pull request #12 from 26730013-NguyenNgocDuy/feat/platform*)
- **Trạng thái Working Tree:** Sạch (`nothing added to commit but untracked files present` gồm `.agents/`, `docs/`, `memorybank/`).
- **Danh sách Local Branches:**
  - `main` (active)
  - `feature/color-theme`
  - `feature/hung-color-theme-ui`
  - `feature/hung-increase-fall-speed`
  - `feature/increase-fall-speed`
- **Danh sách Remote Branches (`origin/*`):**
  - `origin/main` (HEAD của repo chính)
  - `origin/feat/platform` (đã merge vào main qua PR #12)
  - `origin/chore/readme` (đã merge vào main qua PR #10)
  - `origin/feature/add-function-rotate` (đã merge vào main qua PR #6; có thêm 1 commit chưa merge `24ea08b`)
  - `origin/feature/square-border-block` (đã merge vào main qua PR #7)
  - `origin/feature/remove-line` (đã merge vào main qua PR #8; có thêm commit sync `8284f43`)
  - `origin/feature/increase-fall-speed` (đã merge vào main qua PR #1)
  - `origin/feature/hung-increase-fall-speed` (đã merge vào main qua PR #9)
  - `origin/feature/hung-color-theme-ui` (đã merge vào main qua PR #11)
  - `origin/feature/color-theme` (PR #2 đã đóng do trùng lặp)
  - `origin/refactor/core-classes-khang` (**CHƯA MERGE**, nhánh refactor tách class Board, Tetromino, Bag7)
  - `origin/refactor/game-states-khang` (**CHƯA MERGE**, nhánh refactor hoàn thiện State Pattern, Game, Input, Renderer)

---

# 2. Contributors (Chuẩn Hóa Thành Viên & Đóng Góp Thực Tế)

Nhóm gồm 5 thành viên thuộc lớp SS004.F31.CN1.CNTT:

| Thành viên | MSSV & Email Git | Git Username / Author Alias | Tổng commit Git | Vai trò chính thực tế |
| :--- | :--- | :--- | :---: | :--- |
| **Nguyễn Ngọc Duy** | `26730013@ms.uit.edu.vn` | `26730013-NguyenDuy`, `Duy Nguyen` | 10 | Nhóm trưởng, tạo repo, quản lý PR, giải pháp Multi-platform (`Platform.h`, `play.sh`), viết README |
| **Lê Vũ Thảnh** | `26730061@ms.uit.edu.vn` | `26730061 - Lê Vũ Thảnh`, `Lê Vũ Thảnh` | 12 | Triển khai logic xóa hàng `removeLine()` qua các vòng lặp sửa lỗi và PR #8 |
| **Nguyễn Hoàng Khang** | `26730030@ms.uit.edu.vn` | `26730030-Nguyen Hoang Khang`, `Khang-PCC-DT`, `26730030-NguyenHoangKhang` | 16 | Chuẩn hóa viền khối vuông (PR #7) & Kiến trúc sư Refactor toàn bộ sang OOP (14 commits trên 2 branch refactor) |
| **Trần Công Thịnh** | `26730064@ms.uit.edu.vn` | `Tran Cong Thinh` | 4 | Viết thuật toán xoay khối gạch `rotate()`, tự giải quyết merge conflict với `main` (PR #6) |
| **Phạm Phú Nguyễn Hưng** | `26730023@ms.uit.edu.vn` | `Phạm Phú Nguyễn Hưng`, `ppnh10092002@gmail.com` | 15 | Xây dựng bộ điều khiển tốc độ `DropSpeedController.h`, bộ unit test `test_speed.cpp`, HUD màu sắc, Ghost/Hold/Next queue, launcher `Play_Game.bat` |

---

# 3. Branches Audit (Phân Tích Chi Tiết Từng Nhánh)

| Tên Branch | Người làm | Merge-base với `main` | Commits chính | Trạng thái | Đã merge vào đâu | Evidence |
| :--- | :--- | :--- | :--- | :---: | :--- | :--- |
| `feature/square-border-block` | Nguyễn Hoàng Khang | `dc56b3f` | `63b108c` | MERGED | `main` (PR #7) | Commit merge: `e59bf36` |
| `feature/remove-line` | Lê Vũ Thảnh | `e59bf36` | `e893f4f`, `24f087a`, `1782e60`, `81ee914`, `b9391f9`, `5dbf4b9` | MERGED | `main` (PR #8) | Commit merge: `58de5d6` |
| `feature/increase-fall-speed` | Phạm Phú Nguyễn Hưng | `a311e39` | `a98623f`, `23dbf76`, `6c2aef8` | MERGED | `main` (PR #1) | Commit merge: `0a43567` |
| `chore/readme` | Nguyễn Ngọc Duy | `0a43567` | `48e34cd` | MERGED | `main` (PR #10) | Commit merge: `bbb7863` |
| `feature/add-function-rotate` | Trần Công Thịnh | `bb5de88` | `1758d20`, `7dbbd03`, `b78fd52` | MERGED | `main` (PR #6) | Commit merge: `839db64` (giải quyết conflict trực tiếp trên branch) |
| `feature/hung-color-theme-ui` | Phạm Phú Nguyễn Hưng | `839db64` | `e2a55b2`, `48736da` | MERGED | `main` (PR #11) | Commit merge: `eab7383` (giải quyết conflict với rotate) |
| `feature/hung-increase-fall-speed` | Phạm Phú Nguyễn Hưng | `eab7383` | `5f22ffc`, `160e248`, `5280302`, `536a190`, `6648e49` | MERGED | `main` (PR #9) | Commit merge: `d32504c` (Unit test + Combo + HUD speed) |
| `feat/platform` | Nguyễn Ngọc Duy | `d32504c` | `222ff2c` | MERGED | `main` (PR #12) | Commit merge: `cd492e7` (Platform.h, play.sh) |
| `refactor/core-classes-khang` | Nguyễn Hoàng Khang | `cd492e7` (HEAD của main) | `61eb4d6`, `ca0416b`, `d062908`, `3ca6c4f`, `7d66225`, `d2567fc`, `1c3375f`, `9aa2b17` | ACTIVE (Chưa merge) | Đang mở trên remote, chờ review nghiệm thu | `git log main..origin/refactor/core-classes-khang` |
| `refactor/game-states-khang` | Nguyễn Hoàng Khang | `cd492e7` (qua core-classes) | `f773c30`, `c1cf863`, `ffb5a13`, `73b35da`, `906f3b7`, `2bfd916` | ACTIVE (Chưa merge) | Đang mở trên remote, chờ review nghiệm thu | `git log main..origin/refactor/game-states-khang` |

---

# 4. Pull Requests Audit (Kiểm Tra 12 PR Trên GitHub)

Trích xuất trực tiếp từ GitHub CLI API (`gh pr list --state all`):

| PR # | Nhánh nguồn → đích | Tác giả | Tiêu đề PR | Reviewer / Đánh giá | Trạng thái | Thời điểm Merge/Đóng |
| :---: | :--- | :--- | :--- | :--- | :---: | :--- |
| **#1** | `feature/increase-fall-speed` → `main` | Phạm Phú Nguyễn Hưng | feat: increase block fall speed after line clear | Duy / Tự động giải quyết conflict | **MERGED** | 2026-09-18 13:32:06 UTC |
| **#2** | `feature/color-theme` → `main` | Phạm Phú Nguyễn Hưng | feat: add console color themes and square blocks | Nguyễn Ngọc Duy (Owner) | **CLOSED** | Đóng bởi Duy: *"Đóng PR này vì bị duplicate code"* |
| **#3** | `remove-lines` → `main` | Lê Vũ Thảnh | Xong remove lines | Copilot Reviewer (Commented) | **CLOSED** | Đóng để gộp nhánh chuẩn |
| **#4** | `feature/remove-line` → `main` | Lê Vũ Thảnh | Chỉnh remove line | Copilot Reviewer (Commented) | **CLOSED** | Đóng để fix logic xóa biên |
| **#5** | `feature/remove-line` → `main` | Lê Vũ Thảnh | Sửa removeLine() | Copilot Reviewer (Cảnh báo xóa nhầm `src/`) | **CLOSED** | Đóng vì xóa nhầm cây thư mục `src/` |
| **#6** | `feature/add-function-rotate` → `main` | Trần Công Thịnh | Add function rotate | Duy Nguyen (Review & Merge) | **MERGED** | 2026-09-19 03:55:51 UTC |
| **#7** | `feature/square-border-block` → `main` | Nguyễn Hoàng Khang | update square for border | Khang / Duy | **MERGED** | 2026-09-18 11:09:46 UTC |
| **#8** | `feature/remove-line` → `main` | Lê Vũ Thảnh | Feature/remove line | Duy & Khang (Co-review) | **MERGED** | 2026-09-18 11:43:28 UTC |
| **#9** | `feature/hung-increase-fall-speed` → `main` | Phạm Phú Nguyễn Hưng | feat(SV5): increase block fall speed after line clear | Duy Nguyen (Review & Merge) | **MERGED** | 2026-09-21 02:17:21 UTC |
| **#10**| `chore/readme` → `main` | Nguyễn Ngọc Duy | chore: update readme for more exciting | Duy Nguyen | **MERGED** | 2026-09-18 14:00:55 UTC |
| **#11**| `feature/hung-color-theme-ui` → `main` | Phạm Phú Nguyễn Hưng | feat(SV5): complete colored UI, hold piece, next queue & ghost piece | Duy Nguyen (Review & Merge) | **MERGED** | 2026-09-19 04:07:25 UTC |
| **#12**| `feat/platform` → `main` | Nguyễn Ngọc Duy | feat: implemented script which support run on muti-platform | Duy Nguyen | **MERGED** | 2026-09-21 02:46:44 UTC |

---

# 5. Git Timeline (Dòng Thời Gian Phát Triển Thực Tế)

```
2026-09-14
├── 10:26 [Duy]      Commit a311e39: Initial commit
├── 10:38 [Duy]      Commit b1f6d45: Add initial game implementation (main.cpp cơ bản) & README
└── 15:31 [Duy]      Commit bb5de88: Update project description in README.md

2026-09-15
├── 08:41 [Hưng]     Commit a98623f: feat: increase fall speed after clearing lines
├── 08:54 [Hưng]     Commit 60baf55: feat: add color rendering and square blocks theme
├── 08:54 [Hưng]     Commit bd2ee2a: feat: add 1-click launcher script Play_Game.bat
├── 08:57 [Thảnh]    Commit d050f29: First commit (lên thẳng main)
├── 10:07 [Duy]      Commit dc56b3f: Revert "First commit" (khôi phục main an toàn)
├── 10:12 - 10:45    [Thảnh] Phát triển trên nhánh feature/remove-line:
│                    e893f4f -> 24f087a -> 1782e60 -> 81ee914 -> 5b8396c -> b9391f9
└── 01:54 - 03:48    Các PR #2, #3, #4, #5 được mở và đóng để rà soát lỗi logic.

2026-09-16
└── 11:57 [Thịnh]    Commit 1758d20: Add function rotate (trên branch feature/add-function-rotate)

2026-09-18
├── 18:07 [Khang]    Commit 63b108c: update square for border (trên feature/square-border-block)
├── 18:09 [Khang]    Commit e59bf36: MERGE PR #7 (square-border-block -> main)
├── 18:33 [Thảnh]    Commit 5dbf4b9: Edit removeLine() hoàn thiện
├── 18:43 [Thảnh]    Commit 58de5d6: MERGE PR #8 (remove-line -> main)
├── 20:13 [Hưng]     Commit 23dbf76 & 6c2aef8: Resolve conflict với main trên feature/increase-fall-speed
├── 20:32 [Hưng]     Commit 0a43567: MERGE PR #1 (increase-fall-speed -> main)
├── 20:58 [Duy]      Commit 48e34cd: chore: update readme for more exciting
└── 21:00 [Duy]      Commit bbb7863: MERGE PR #10 (chore/readme -> main)

2026-09-19
├── 09:58 [Thịnh]    Commit 7dbbd03: fix conflict trên feature/add-function-rotate với main
├── 10:53 [Thịnh]    Commit b78fd52: Update README.md
├── 10:55 [Duy]      Commit 839db64: MERGE PR #6 (add-function-rotate -> main)
├── 10:58 [Hưng]     Commit e2a55b2: feat(SV5): integrate full color UI, hold piece, next queue, ghost piece
├── 11:02 [Hưng]     Commit 48736da: chore: resolve merge conflict với main (tích hợp rotate + colored UI)
└── 11:07 [Duy]      Commit eab7383: MERGE PR #11 (hung-color-theme-ui -> main)

2026-09-21
├── 09:15 [Hưng]     Commit 5f22ffc, 160e248, 5280302, 536a190, 6648e49: Tách module DropSpeedController.h,
│                    bổ sung Combo Streak, Level, HUD speed, bộ kiểm thử test_speed.cpp (6/6 tests pass)
├── 09:17 [Hưng]     Commit d32504c: MERGE PR #9 (hung-increase-fall-speed -> main)
├── 09:45 [Duy]      Commit 222ff2c: Tạo Platform.h (POSIX termios + Windows API), script play.sh
├── 09:46 [Duy]      Commit cd492e7: MERGE PR #12 (feat/platform -> main) == HEAD CỦA MAIN HIỆN TẠI
├── 09:58 - 11:03    [Khang] BẮT ĐẦU REFACTOR OOP (Branch refactor/core-classes-khang):
│                    61eb4d6 -> ca0416b (Tetromino) -> d062908 -> 3ca6c4f -> 7d66225 (Board) ->
│                    d2567fc -> 1c3375f (Bag7 + Board rules) -> 9aa2b17 (Vietnamese comments)
└── 11:18 - 11:32    [Khang] HOÀN THIỆN STATE PATTERN (Branch refactor/game-states-khang):
                     f773c30 (Renderer) -> c1cf863 (Input) -> ffb5a13 (Game class) ->
                     73b35da (GameState) -> 906f3b7 (Pause/Restart) -> 2bfd916 (README update)
```

---

# 6. OOP Architecture Analysis (Phân Tích Kiến Trúc Hướng Đối Tượng)

Trong nhánh `refactor/game-states-khang`, kiến trúc OOP được triển khai chuẩn mực với 7 lớp cốt lõi:

```
                  +-----------------------------------+
                  |               Game                |
                  +-----------------------------------+
                   | owns  | owns   | owns  | owns  | owns
        +----------+       |        |       |       +----------+
        |                  |        |       |                  |
        v                  v        v       v                  v
+---------------+  +-----------+  +----+  +--------+  +--------------------+
|     Board     |  | Tetromino |  |Bag7|  |Renderer|  |DropSpeedController |
+---------------+  +-----------+  +----+  +--------+  +--------------------+
        ^                ^                     ^
        |                | uses                |
        +----------------+                     |
                                               |
                  +-------------------+        |
                  |     GameState     |--------+
                  +-------------------+
                   ^        ^        ^
                   |        |        | (Inheritance)
    +--------------+        |        +--------------+
    |                       |                       |
+--------------+   +---------------+   +-------------------+
| PlayingState |   |  PausedState  |   |   GameOverState   |
+--------------+   +---------------+   +-------------------+
```

### 4 Trụ Cột OOP Được Chứng Minh Bằng Code Thực Tế:

1. **Tính Đóng Gói (Encapsulation):**
   - Lớp `Board`: Mảng `grid[ROWS][COLS]` được đặt ở `private`. Toàn bộ thao tác đọc/ghi phải thông qua phương thức kiểm soát biên: `at(r, c)`, `set(r, c, val)`, `canPlace(piece, dx, dy)`. Triệt tiêu hoàn toàn lỗi tràn mảng hoặc ghi đè viền.
   - Lớp `Tetromino`: Mảng hình dạng khối `shape[4][4]`, tọa độ `posX, posY`, mã khối `type` được bảo vệ chặt chẽ; bên ngoài chỉ truy cập qua `isFilled()`, `getX()`, `getY()`.
   - Lớp `DropSpeedController`: Thuộc tính `currentIntervalMs`, `comboStreak`, `comboScore`, `level` được quản lý nội tại; cập nhật thông qua `onLineCleared(lines)`.

2. **Tính Kế Thừa (Inheritance):**
   - Lớp trừu tượng `GameState`:
     ```cpp
     class GameState {
     protected:
         Game *game;
     public:
         virtual void handle(Action action) = 0;
         virtual void update() = 0;
         virtual void draw() = 0;
         virtual int tickMs() const { return 80; }
     };
     ```
   - 3 lớp con kế thừa: `PlayingState`, `PausedState`, `GameOverState`.

3. **Tính Đa Hình (Polymorphism):**
   - Được thể hiện tại con trỏ `GameState *state` trong `Game`.
   - Vòng lặp `Game::run()` chỉ cần thực thi:
     `state->handle(act); state->update(); state->draw();`
   - Tại runtime, khi ở trạng thái `PlayingState`, game xử lý di chuyển và trọng lực; khi bấm 'P', chuyển sang `PausedState`, game ngừng rơi gạch và chỉ chờ lệnh tiếp tục; khi thua, chuyển sang `GameOverState` để hiển thị điểm tổng.

4. **Tính Trừu Tượng (Abstraction):**
   - Lớp `Input`: Trừu tượng hóa bàn phím bằng kiểu liệt kê `enum Action` (`ACTION_LEFT`, `ACTION_ROTATE`, `ACTION_PAUSE`...). Mã game không còn so sánh ký tự cứng `'w'`, `'a'`, `'s'`, `'d'`.
   - Lớp `Renderer`: Tách biệt hoàn toàn phần giao diện (UI) khỏi dữ liệu game. Phương thức `draw(...)` chỉ nhận các tham chiếu `const` để hiển thị.

---

# 7. Before vs After OOP Refactor (Đối Chiếu Trước & Sau Khi Refactor)

| Tiêu chí | Trước Refactor (`main` hiện tại - `cd492e7`) | Sau Refactor (`refactor/game-states-khang` - `2bfd916`) | Commit minh chứng | Ý nghĩa OOP |
| :--- | :--- | :--- | :--- | :--- |
| **Điểm vào `main.cpp`** | ~550 dòng chứa toàn bộ game loop, switch phím, logic mảng | 17 dòng: `srand(); Game game; game.run();` | `ffb5a13` | Tách biệt trách nhiệm (Single Responsibility) |
| **Quản lý Bàn Cờ** | Mảng toàn cục `char board[H][W]`, define `H 20`, `W 12` | `class Board` với `grid` private, hằng số `ROWS, COLS` | `7d66225`, `d2567fc` | Đóng gói dữ liệu (Encapsulation) |
| **Xóa Hàng** | Hàm tự do `int removeLine()` thao tác trực tiếp trên `board[][]` | `Board::isRowFull()` và `Board::removeRow()` | `1c3375f` | Phân rã logic thành các phương thức có kiểm soát |
| **Khối Gạch Đang Rơi** | 4 biến toàn cục rời rạc: `cur[4][4]`, `x`, `y`, `b` | `class Tetromino` gom dữ liệu và tọa độ thành 1 đối tượng | `ca0416b`, `d062908` | Mô hình hóa thực thể hướng đối tượng |
| **Xoay Khối Gạch** | Hàm `rotate()` thao tác trên mảng tạm `tmp[4][4]` rồi gán lại | Phương thức `Tetromino::rotated() const` trả về bản sao | `ca0416b` | Bất biến (Immutability) & An toàn dữ liệu |
| **Sinh Khối Mới** | `spawn()` dùng `rand() % 7` (dễ bị trùng liên tiếp nhiều lần) | `class Bag7` xáo trộn túi 7 khối theo Tetris Guideline | `1c3375f` | Trừu tượng hóa thuật toán sinh số |
| **Điều Khiển Game** | Biến cờ `gameOver`, vòng lặp `while(1)` lồng lệnh `_kbhit()` | State Pattern: `GameState`, `PlayingState`, `PausedState` | `73b35da` | Đa hình (Polymorphism) & Quản lý trạng thái |
| **Giao Diện / Vẽ** | Hàm `draw()` trộn lẫn console API và truy cập biến toàn cục | `class Renderer` nhận tham chiếu `const`, chuyên biệt hiển thị | `f773c30` | Phân tách giao diện và logic (Separation of Concerns) |

---

# 8. Feature Traceability (Bảng Truy Vết Tính Năng Mã Nguồn)

| STT | Tính năng | File triển khai | Lớp / Phương thức / Hàm | Commit đưa vào | Contributor | Trạng thái |
| :---: | :--- | :--- | :--- | :--- | :--- | :---: |
| 1 | Khởi tạo bàn cờ & khung | `main.cpp` / `Board.cpp` | `initBoard()` / `Board::reset()` | `b1f6d45`, `7d66225` | Duy, Khang | **IMPLEMENTED** |
| 2 | Viền vuông bàn cờ | `main.cpp` / `Board.h` | Ký tự CP437 / `WALL = '#'` | `63b108c` (PR #7) | Khang | **IMPLEMENTED** |
| 3 | Xoay khối Tetromino | `main.cpp` / `Tetromino.cpp` | `rotate()` / `Tetromino::rotated()` | `1758d20` (PR #6), `ca0416b`| Thịnh, Khang | **IMPLEMENTED** |
| 4 | Kiểm tra va chạm (Collision) | `main.cpp` / `Board.cpp` | `canMove()` / `Board::canPlace()` | `b1f6d45`, `1c3375f` | Duy, Khang | **IMPLEMENTED** |
| 5 | Khóa khối gạch (Lock piece) | `main.cpp` / `Board.cpp` | `block2Board()` / `Board::place()` | `b1f6d45`, `1c3375f` | Duy, Khang | **IMPLEMENTED** |
| 6 | Xóa hàng đầy (Remove line) | `main.cpp` / `Board.cpp` | `removeLine()` / `Board::removeRow()` | `5dbf4b9` (PR #8), `1c3375f`| Thảnh, Khang | **IMPLEMENTED** |
| 7 | Tăng tốc độ rơi sau xóa hàng | `DropSpeedController.h` | `DropSpeedController::onLineCleared` | `a98623f` (PR #1), `5f22ffc` | Hưng | **IMPLEMENTED** |
| 8 | Hệ số Combo Streak & Điểm số | `DropSpeedController.h` | `calculateLineScore()`, `comboStreak` | `5f22ffc` (PR #9) | Hưng | **IMPLEMENTED** |
| 9 | Kiểm thử tự động (Unit Test) | `test_speed.cpp` | 6/6 test cases (Speed, Combo, Cap) | `5280302` (PR #9) | Hưng | **IMPLEMENTED** |
| 10| Giao diện ANSI, Khử giật | `ColorRenderer.h` / `Renderer.cpp` | `gotoxy()`, `hideCursor()`, `draw()` | `60baf55`, `e2a55b2`, `f773c30`| Hưng, Khang | **IMPLEMENTED** |
| 11| Ghost Piece, Hold, Next Queue | `main.cpp` / `Game.cpp` | `getGhostY()`, `holdPiece()`, queue | `e2a55b2` (PR #11), `ffb5a13`| Hưng, Khang | **IMPLEMENTED** |
| 12| Đa nền tảng (macOS / Linux) | `Platform.h`, `play.sh` | Cross-platform termios, ANSI colors | `222ff2c` (PR #12) | Duy | **IMPLEMENTED** |
| 13| Tạm dừng & Chơi lại (P/R) | `GameState.h`, `Game.cpp` | `PausedState`, `GameOverState` | `73b35da`, `906f3b7` | Khang | **IMPLEMENTED** |
| 14| Sinh khối túi 7 (Bag-7) | `Bag7.h`, `Bag7.cpp` | `Bag7::next()`, `Bag7::refill()` | `1c3375f` | Khang | **IMPLEMENTED** |

---

# 9. Claim Verification (Đối Chiếu Khẳng Định Trello / Báo Cáo Với Git)

| Yêu cầu / Khẳng định (Claim) | Người phụ trách | Bằng chứng từ Git (Commit / PR) | Mức độ xác minh | Ghi chú kỹ thuật |
| :--- | :--- | :--- | :---: | :--- |
| Chuyển struct sang class & hoàn thiện game | Nguyễn Hoàng Khang | 14 commits trên 2 nhánh `refactor/core-classes-khang` và `refactor/game-states-khang` | **VERIFIED** | Tách 7 class OOP hoàn chỉnh, rút gọn main.cpp còn 17 dòng; hiện nằm trên branch refactor |
| Viết cấu hình đa nền tảng macOS/Linux | Nguyễn Ngọc Duy | Commit `222ff2c`, PR #12 (`Platform.h`, `play.sh`) | **VERIFIED** | Tương thích song song Windows Console API và POSIX `termios` |
| Nghiên cứu và viết code xoay khối `rotate()` | Trần Công Thịnh | Commit `1758d20`, commit giải quyết conflict `7dbbd03`, PR #6 | **VERIFIED** | Viết thuật toán xoay ma trận và tự xử lý xung đột code với nhánh `main` |
| Thiết kế viền bàn cờ và khối vuông vức | Nguyễn Hoàng Khang | Commit `63b108c`, PR #7 | **VERIFIED** | Chuẩn hóa bảng mã ký tự CP437 cho viền và block |
| Viết code tăng tốc rơi & bộ điều tốc | Phạm Phú Nguyễn Hưng | Commits `a98623f`, `5f22ffc`, `5280302`, PR #1, PR #9 | **VERIFIED** | Xây dựng `DropSpeedController.h`, kiểm thử tự động `test_speed.cpp` |
| Viết thuật toán xóa hàng `removeLine()` | Lê Vũ Thảnh | Commits `e893f4f`, `81ee914`, `5dbf4b9`, PR #8 | **VERIFIED** | Trải qua 4 lần sửa đổi để khắc phục lỗi xóa mất biên tường cờ |
| Viết lại README chuyên nghiệp, hấp dẫn | Nguyễn Ngọc Duy | Commit `48e34cd`, PR #10 | **VERIFIED** | Cập nhật cấu trúc hướng dẫn, bảng phím và mô tả lối chơi |
| Bổ sung giao diện màu ANSI, Ghost, Hold | Phạm Phú Nguyễn Hưng | Commit `60baf55`, `e2a55b2`, PR #11 | **VERIFIED** | Tích hợp HUD 3 khung, Ghost piece và Hold piece |
| Khắc phục merge conflict thực tế | Thịnh, Hưng, Duy | Commits: `7dbbd03` (Thịnh), `48736da` (Hưng), `dc56b3f` (Duy) | **VERIFIED** | Lịch sử Git ghi nhận rõ ràng các commit merge conflict |
| Soạn thảo hợp đồng nhóm | Cả nhóm | Nội dung hợp đồng trong tài liệu báo cáo `docs/` | **PARTIALLY VERIFIED** | Có trong hồ sơ báo cáo nhóm; không tạo file source code riêng |

---

# 10. Collaboration Analysis (Phân Tích Hợp Tác Nhóm Thực Tế)

### 3 Tình Huống Xung Đột & Xử Lý Thực Tế (Merge Conflicts & Resolutions):

1. **Sự cố Revert Commit đầu tiên (15/09):**
   - **Tình huống:** Thành viên SV2 (Thảnh) push commit `d050f29` trực tiếp lên `main` làm xáo trộn cấu trúc repo.
   - **Giải quyết:** Nhóm trưởng SV1 (Duy) ngay lập tức thực hiện commit `dc56b3f` (`Revert "First commit"`), thiết lập nguyên tắc cấm push trực tiếp lên `main`, yêu cầu 100% qua nhánh tính năng và PR.

2. **Xung đột khi tích hợp hàm xoay `rotate()` của SV4 (19/09):**
   - **Tình huống:** Nhánh `feature/add-function-rotate` của Thịnh được tạo từ ngày 16/09 (commit `bb5de88`). Trong thời gian đó, `main` đã merge các PR của Khang (#7), Thảnh (#8), Hưng (#1) và Duy (#10). Khi mở PR #6, nhánh bị conflict nghiêm trọng với `main`.
   - **Giải quyết:** Thành viên Thịnh chủ động pull `main` về nhánh của mình, giải quyết xung đột bằng tay tại commit `7dbbd03` ("fix conflict"), kiểm tra lại và được Duy merge qua commit `839db64`.

3. **Xung đột khi tích hợp giao diện màu và HUD của SV5 (19/09):**
   - **Tình huống:** Hưng phát triển nhánh `feature/hung-color-theme-ui` trên nền cũ. Khi nhánh `rotate()` của Thịnh vừa được merge vào `main`, code hiển thị của Hưng bị đè lên các hàm phím bấm mới.
   - **Giải quyết:** Hưng thực hiện commit merge `48736da` ("chore: resolve merge conflict with origin/main (integrate rotate and colored UI HUD)"), kiểm tra hiển thị đồng bộ cả xoay khối và màu sắc trước khi merge qua PR #11.

---

# 11. Evidence Index (Chỉ Mục 10 Minh Chứng Mạnh Nhất Để Trình Chiếu)

| Mã Minh chứng | Loại minh chứng | Lệnh Git / Mã thực tế | Mục đích chứng minh trước Giảng viên |
| :---: | :--- | :--- | :--- |
| **EVD-01** | Git Graph | `git log --all --graph --oneline --decorate -n 30` | Quy trình phân nhánh tính năng (Git Flow) và lịch sử merge rõ ràng |
| **EVD-02** | GitHub PR List | `gh pr list --state all` | Quản lý 12 Pull Requests có trạng thái rõ ràng, đóng mở có lý do |
| **EVD-03** | Commit Revert | `git show dc56b3f` | Kỷ luật làm việc nhóm: Leader revert commit sai quy định để bảo vệ `main` |
| **EVD-04** | Conflict Resolve | `git show 7dbbd03` (Thịnh) & `48736da` (Hưng) | Năng lực giải quyết xung đột mã nguồn thực tế của từng thành viên |
| **EVD-05** | Copilot Review | Review comment tại PR #5 | Sử dụng AI Code Review cảnh báo lỗi xóa nhầm thư mục `src/` |
| **EVD-06** | Unit Test Suite | `g++ -O2 test_speed.cpp -o test_speed.exe; ./test_speed.exe` | Đảm bảo chất lượng: 6/6 test cases kiểm thử logic DropSpeedController PASS |
| **EVD-07** | OOP Refactor Diff | `git diff main origin/refactor/game-states-khang --stat` | Khang refactor toàn diện: thêm 7 class OOP, rút gọn `main.cpp` còn 17 dòng |
| **EVD-08** | Encapsulation | `git show origin/refactor/game-states-khang:Board.h` | Đóng gói mảng `grid` ở private, kiểm soát đọc ghi bằng `at()` và `canPlace()` |
| **EVD-09** | State Pattern | `git show origin/refactor/game-states-khang:GameState.h` | Tính Đa hình (Polymorphism) với lớp trừu tượng `GameState` và 3 state con |
| **EVD-10** | Cross-Platform | `Platform.h` & `play.sh` | Thiết kế trừu tượng hóa hệ điều hành, chạy mượt trên cả Windows và Linux/macOS |

---

# 12. Kế Hoạch Trình Bày Báo Cáo (12–15 Phút) & Đề Xuất Slide

### Phân Bổ Thời Gian Chuẩn:
1. **00:00 - 00:30 (0.5p):** Tổng quan dự án & Mục tiêu trọng tâm (Không nói luật chơi Tetris).
2. **00:30 - 02:30 (2.0p):** Quy trình làm việc nhóm & Môi trường cộng tác số (Trello, Slack, GitHub).
3. **02:30 - 04:00 (1.5p):** Phân công công việc & Quản lý tiến độ thực tế (Bảng ma trận trách nhiệm).
4. **04:00 - 06:00 (2.0p):** Git Workflow, Phân nhánh tính năng & Lịch sử Pull Requests.
5. **06:00 - 09:00 (3.0p):** Kiến trúc hướng đối tượng (OOP Architecture: Before vs After).
6. **09:00 - 11:30 (2.5p):** Minh chứng kỹ thuật tiêu biểu: Unit Test, State Pattern, Đóng gói Board.
7. **11:30 - 13:00 (1.5p):** Tinh thần hợp tác: Xử lý Merge Conflicts, Code Review chéo.
8. **13:00 - 14:30 (1.5p):** Kết quả đạt được, bài học kinh nghiệm & Q&A.

---

### Outline 10 Slide Trình Chiếu Chi Tiết:

#### Slide 1: Project Snapshot & Team Intro (Người nói: Duy - 0.5p)
- **Tiêu đề:** Đồ Án Tetris_UIT — Nhóm Hidden Gem (SS004)
- **Ý chính:** Giới thiệu thành viên, mục tiêu rèn luyện kỹ năng làm việc nhóm kỹ thuật số, phát triển game bằng C++ thuần không dùng engine.
- **Evidence:** Bảng thông tin 5 thành viên và GitHub repo banner.

#### Slide 2: Digital Collaboration Workspace (Người nói: Duy - 1p)
- **Tiêu đề:** Môi Trường Cộng Tác Số: GitHub, Trello & Slack
- **Ý chính:** Trello Kanban phân loại To Do / In Progress / Review / Done; GitHub là Single Source of Truth; Slack trao đổi kỹ thuật thời gian thực.
- **Evidence:** Screenshot bảng Kanban Trello và kênh Slack nhóm.

#### Slide 3: Task Allocation Matrix (Người nói: Duy - 1p)
- **Tiêu đề:** Ma Trận Phân Công & Điều Chỉnh Thực Tế
- **Ý chính:** Phân công ban đầu theo module độc lập; linh hoạt điều chỉnh khi xuất hiện yêu cầu mở rộng (OOP refactor, UI colors, multi-platform).
- **Evidence:** Bảng đối chiếu Ban đầu vs Thực tế (mục 4.1 trong tài liệu này).

#### Slide 4: Git Workflow & Pull Requests (Người nói: Hưng - 2p)
- **Tiêu đề:** Quy Trình Git Flow & Kiểm Soát Mã Nguồn
- **Ý chính:** 100% tính năng đi qua feature branch; 12 Pull Requests có thảo luận, review và đóng/merge có căn cứ; cấm push trực tiếp vào `main`.
- **Evidence:** **EVD-01** (Git graph) và **EVD-02** (Danh sách PR qua `gh pr list`).

#### Slide 5: Architecture Evolution: Procedural to OOP (Người nói: Khang - 1.5p)
- **Tiêu đề:** Quá Trình Chuyển Đổi: Từ Thủ Tục Sang OOP
- **Ý chính:** Giai đoạn 1 code tập trung trên `main.cpp` để chạy được nhanh; Giai đoạn 2 Khang refactor toàn diện thành 7 lớp đối tượng chuẩn mực.
- **Evidence:** Bảng so sánh Trước/Sau (Before vs After) và rút gọn `main.cpp` từ 550 dòng xuống 17 dòng.

#### Slide 6: Deep Dive OOP Principles (Người nói: Khang - 1.5p)
- **Tiêu đề:** Hiện Thực Hóa 4 Trụ Cột OOP Trong Mã Nguồn
- **Ý chính:** Encapsulation (`Board`, `Tetromino`), Abstraction (`Input`, `Renderer`), Inheritance & Polymorphism (`GameState` -> `Playing`, `Paused`, `GameOver`).
- **Evidence:** **EVD-08** (`Board.h`) và **EVD-09** (`GameState.h`).

#### Slide 7: Game Mechanics & Quality Assurance (Người nói: Hưng - 1.5p)
- **Tiêu đề:** Đảm Bảo Chất Lượng: Unit Test & Cơ Chế Gia Tốc
- **Ý chính:** Thiết kế `DropSpeedController.h` độc lập; bộ kiểm thử tự động `test_speed.cpp` chứng minh logic không lỗi góc (Zero Edge-case Bug).
- **Evidence:** **EVD-06** (Terminal chạy `test_speed.exe` 6/6 tests pass).

#### Slide 8: Team Collaboration & Conflict Resolution (Người nói: Thịnh / Thảnh - 1.5p)
- **Tiêu đề:** Xử Lý Xung Đột Mã Nguồn & Code Review Chéo
- **Ý chính:** Thịnh tự fix conflict nhánh `rotate()`; Thảnh kiên trì hoàn thiện `removeLine()` qua 4 vòng lặp; vai trò Co-reviewer của Khang.
- **Evidence:** **EVD-03** (Revert commit), **EVD-04** (Merge conflict commit `7dbbd03`), **EVD-05** (Copilot review PR #5).

#### Slide 9: Live Demo & Multi-Platform Execution (Người nói: Duy - 1.5p)
- **Tiêu đề:** Sản Phẩm Hoàn Chỉnh & Khả Năng Chạy Đa Nền Tảng
- **Ý chính:** Chạy mượt mà 1-click trên Windows (`Play_Game.bat`) và macOS/Linux (`play.sh`); giao diện không giật, hỗ trợ Hold, Ghost, Next queue.
- **Evidence:** Trình diễn cửa sổ game console thực tế.

#### Slide 10: Lessons Learned & Team Reflection (Người nói: Duy - 1p)
- **Tiêu đề:** Bài Học Kinh Nghiệm Trong Làm Việc Nhóm Kỹ Thuật Số
- **Ý chính:** Bài học về giao tiếp sớm để tránh conflict; bài học về thiết kế cấu trúc lớp ngay từ đầu; kinh nghiệm phân chia công việc công bằng.
- **Evidence:** Slide tóm tắt thành quả và cam kết học tập.

---

# 13. Speaker Notes & Live Action Guide (Kịch Bản Thao Tác Chi Tiết)

### Hướng dẫn thao tác màn hình theo từng phút:

- **Phút 00:00 - 02:30 (Mở đầu & Trello):**
  - *Hành động màn hình:* Mở trình duyệt tại tab **Trello Workspace**.
  - *Chỉ vào:* Cột "Done" với các thẻ có nhãn màu sắc, hạn chót và thành viên được gán thẻ.
  - *Lời thoại mẫu:* "Thưa thầy, nhóm Hidden Gem không bắt đầu bằng việc code ngay lập tức mà thiết lập bảng cộng tác Trello và thỏa thuận nhóm..."

- **Phút 02:30 - 06:00 (Git & Pull Requests):**
  - *Hành động màn hình:* Chuyển sang tab **GitHub Repository** -> mục **Pull Requests**.
  - *Chỉ vào:* PR #1, PR #6, PR #8, PR #9, PR #11, PR #12. Mở PR #5 chỉ ra review của Copilot và lý do tại sao nhóm đóng PR này để sửa lại.
  - *Mở Terminal VS Code:* Gõ lệnh `git log --all --graph --oneline --decorate -n 25` để thầy thấy trực quan các nhánh song song hội tụ về `main`.

- **Phút 06:00 - 09:00 (OOP Refactor):**
  - *Hành động màn hình:* Mở IDE tại nhánh `origin/refactor/game-states-khang`.
  - *Mở song song 2 file:* `main.cpp` (chỉ 17 dòng) và `Game.h` / `Board.h`.
  - *Chỉ vào code:* `Board.h` dòng khai báo `private: char grid[ROWS][COLS];` và các hàm `canPlace()`, `place()`. Mở `GameState.h` chỉ ra 3 hàm thuần ảo `handle()`, `update()`, `draw()`.
  - *Lời thoại mẫu:* "Ban đầu nhóm tích hợp các hàm vào main.cpp để kiểm thử tính năng nhanh. Sau khi các chức năng cơ bản chạy ổn, Khang đã đóng vai trò kiến trúc sư, refactor toàn bộ sang chuẩn OOP với 7 lớp đối tượng, giải quyết triệt để biến toàn cục."

- **Phút 09:00 - 11:30 (Unit Test & Cơ Chế Game):**
  - *Hành động màn hình:* Tại Terminal, chạy lệnh:
    `g++ -O2 test_speed.cpp -o test_speed.exe; ./test_speed.exe`
  - *Chỉ vào màn hình:* 6 dòng kết quả `[PASS] Test 1... Test 6`.
  - *Lời thoại mẫu:* "Nhóm áp dụng nguyên tắc kiểm thử nghiêm ngặt: test pass thôi là chưa đủ, mà giá trị input/output phải khớp domain business. File test_speed kiểm thử độc lập cơ chế gia tốc rơi và combo streak."

- **Phút 11:30 - 13:00 (Collaboration & Conflict):**
  - *Hành động màn hình:* Gõ `git show 7dbbd03` và `git show 48736da`.
  - *Lời thoại mẫu:* "Đây là minh chứng cho việc các thành viên thực sự gặp xung đột mã nguồn khi ghép nối hàm xoay của Thịnh và giao diện của Hưng, và các bạn đã tự giải quyết xung đột bằng lệnh merge cẩn thận."

- **Phút 13:00 - Hết (Chạy Game Thực Tế):**
  - *Hành động màn hình:* Click đúp vào `Play_Game.bat` (hoặc chạy `./play.sh`).
  - *Thao tác:* Bấm phím xoay `W`, giữ phím `C`, đẩy rơi nhanh `X`, bấm `P` để tạm dừng game, bấm tiếp `P` để chơi tiếp.
