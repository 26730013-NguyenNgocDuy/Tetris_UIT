# BÁO CÁO CHUYÊN ĐỀ LÀM VIỆC NHÓM (MÔN HỌC SS004)
## ĐỀ TÀI: MÔ TẢ QUÁ TRÌNH LÀM VIỆC NHÓM TRONG DỰ ÁN TETRIS_UIT

- **Trường:** Đại học Công nghệ Thông tin - ĐHQG TP.HCM (UIT)
- **Khoa:** Công nghệ Thông tin
- **Môn học:** Kỹ năng nghề nghiệp (Mã lớp: SS004.F31.CN1.CNTT) - Học kỳ 3 (Năm học 2025 - 2026)
- **Giảng viên hướng dẫn:** ThS. Nguyễn Văn Toàn (`toannv@uit.edu.vn`)
- **Tên nhóm:** Hidden Gem (Nhóm dự án Tetris_UIT)
- **Người thực hiện:** Phạm Phú Nguyễn Hưng (MSSV: 26730023 - Thành viên SV5)
- **Thẻ Trello phụ trách:** *Mô tả quá trình làm việc nhóm* (Nhãn: *Report* - Hạn chót: 12:00 ngày 21/09/2026)
- **Độ dài văn bản:** 4 trang chuẩn A4 (Đáp ứng quy định: Tối thiểu 2 trang, tối đa 5 trang)

---

## I. TỔNG QUAN DỰ ÁN VÀ MÔI TRƯỜNG CỘNG TÁC SỐ

### 1.1. Bối cảnh và mục tiêu dự án
Trong khuôn khổ môn học **Kỹ năng nghề nghiệp (SS004)**, nhóm nhận nhiệm vụ phát triển một trò chơi cổ điển điều khiển trên màn hình dòng lệnh Windows Console bằng ngôn ngữ C++ thuần mang tên **Tetris_UIT**. Mục tiêu trọng tâm của bài tập không chỉ dừng lại ở mặt kỹ thuật lập trình mà là **thực hành kỹ năng làm việc nhóm song song trong môi trường kỹ thuật số**, mô phỏng chính xác quy trình phát triển phần mềm chuẩn Agile/Scrum mà các kỹ sư phần mềm thực hiện tại các doanh nghiệp công nghệ:
1. Phân chia module công việc độc lập giữa các thành viên.
2. Quản lý tiến độ minh bạch thông qua bảng Kanban trực quan trên Trello.
3. Giao tiếp, giải quyết sự cố kỹ thuật và thảo luận liên tục qua Slack.
4. Quản lý mã nguồn tập trung, phân nhánh tính năng (Git Flow), xử lý các xung đột hợp nhất (Merge Conflicts) thực tế và nghiệm thu mã nguồn thông qua Pull Requests có ít nhất hai người xét duyệt (Code Reviewers).

### 1.2. Thiết lập không gian làm việc số (Digital Collaboration Tools)
Để đảm bảo tính minh bạch, tức thời và truy vết được mọi đóng góp của từng cá nhân, nhóm đã kích hoạt 3 nền tảng chính:

* **GitHub Repository (`https://github.com/26730013-NguyenNgocDuy/Tetris_UIT`):**
  Là "nguồn chân lý duy nhất" (Single Source of Truth - SSOT) của mã nguồn. Toàn bộ tiến trình phát triển được thực hiện trên các nhánh con `feature/*`, `feat/*`, `refactor/*` và `chore/*`, bảo vệ nhánh `main` không bị đẩy code tùy tiện.
* **Trello Kanban Workspace:**
  Thiết lập bảng theo dõi trạng thái công việc với 4 cột chuẩn: **To Do** (Việc cần làm), **In Progress** (Đang triển khai), **Review / Testing** (Kiểm thử & Đánh giá) và **Completed** (Đã hoàn thành). Mỗi thẻ công việc đều có thành viên chịu trách nhiệm chính (Assignee), nhãn định danh (Feature, Bug, Refactor, Report) và ngày đến hạn (Due Date) được cảnh báo tự động.
* **Kênh trao đổi Slack (`ss004f31.slack.com` - Kênh `#tetris-uit-team`):**
  Nơi diễn ra các buổi họp ngắn (Standup Meeting), trao đổi kỹ thuật thời gian thực, tích hợp GitHub Webhook để gửi thông báo tự động mỗi khi có commit mới hoặc Pull Request được mở.

### 1.3. Cơ cấu nhân sự và Phân công công việc ban đầu (Initial Task Allocation)
Dự án có sự tham gia của 5 thành viên. Dựa trên năng lực chuyên môn và sở trường cá nhân, Trưởng nhóm đã phân bổ các đầu việc ban đầu như sau:

| STT | Họ và Tên | MSSV | Vai trò ban đầu | Nhiệm vụ chính được giao trên Trello/Git |
| :---: | :--- | :---: | :---: | :--- |
| **SV1** | **Nguyễn Ngọc Duy** | 26730013 | Trưởng nhóm (PM) | Khởi tạo repo, thiết kế khung sườn `main.cpp`, quản lý Kanban Trello, review & merge PR. |
| **SV2** | **Lê Vũ Thảnh** | 26730061 | Thành viên | Viết thuật toán xóa hàng khi đầy `removeLine()` (Nhánh `feature/remove-line`). |
| **SV3** | **Nguyễn Hoàng Khang** | 26730030 | Thành viên | Tái thiết kế giao diện viền bàn cờ và khối gạch vuông vức (Nhánh `feature/square-border-block`). |
| **SV4** | **Trần Công Thịnh** | 26730064 | Thành viên | Viết giải thuật xoay khối gạch Tetromino theo chiều kim đồng hồ `rotate()` (Nhánh `feature/add-function-rotate`). |
| **SV5** | **Phạm Phú Nguyễn Hưng** | 26730023 | Thành viên | Viết cơ chế tăng tốc độ rơi của khối sau mỗi lần phá hàng (Nhánh `feature/increase-fall-speed`). |

---

## II. CÁC GIAI ĐOẠN TRIỂN KHAI THỰC TẾ (TIMELINE & PHASES)

Dựa trên lịch sử commit trên Git, các cuộc hội thoại trao đổi trên Slack và lịch sử cập nhật thẻ công việc trên Trello, quá trình làm việc nhóm đã trải qua **5 giai đoạn chính** từ ngày 14/09/2026 đến ngày 21/09/2026:

```
[14/09] Giai đoạn 1: Khởi động & Thiết lập khung sườn cơ bản
   │
[15/09 - 16/09] Giai đoạn 2: Phát triển song song & Khủng hoảng Merge Conflict đầu tiên
   │
[17/09 - 18/09] Giai đoạn 3: Họp khẩn cấp, Tái cấu trúc Modular & Phân chia lại công việc
   │
[19/09 - 20/09] Giai đoạn 4: Giải quyết xung đột, Tích hợp HUD màu sắc & Review chéo
   │
[21/09] Giai đoạn 5: Đa nền tảng, Đột phá Refactor OOP toàn diện & Hoàn thiện báo cáo
```

### 2.1. Giai đoạn 1: Khởi tạo và thiết lập khung dự án (Ngày 14/09/2026)
* **Hoạt động thực tế:**
  - Nhóm trưởng Nguyễn Ngọc Duy khởi tạo repository rỗng, tải lên phiên bản cấu trúc dữ liệu nền tảng ban đầu qua các commit `a311e39` ("Initial commit"), `b1f6d45` ("Add initial game implementation and README content for Tetris_UIT") và `bb5de88` ("Update project description in README.md").
  - Họp phiên đầu tiên trên Slack thống nhất quy định: toàn bộ logic game chạy trên một file `main.cpp` để đơn giản hóa việc biên dịch bằng lệnh `g++ main.cpp -o Tetris.exe`.
* **Kết quả đạt được:** Bàn chơi console 13x18 ô với ký tự thô sơ đã có thể chạy được, các khối cơ bản tự rơi từ trên xuống.

### 2.2. Giai đoạn 2: Phát triển song song và Khủng hoảng xung đột mã nguồn (15/09 - 16/09/2026)
* **Hoạt động thực tế:**
  - Các thành viên tạo nhánh cá nhân từ nhánh `main` và bắt đầu lập trình tính năng được giao.
  - **Sự cố Kỷ luật Git đầu tiên (15/09):** Thành viên SV2 (Lê Vũ Thảnh) push commit `d050f29` trực tiếp lên nhánh `main`. Nhóm trưởng Duy lập tức thực hiện commit `dc56b3f` (`Revert "First commit"`) để khôi phục trạng thái sạch của `main` và ban hành quy tắc bắt buộc 100% code phải đi qua nhánh riêng.
  - **SV2 (Lê Vũ Thảnh):** Bắt đầu viết hàm `removeLine()`. Tuy nhiên, do chưa nắm vững việc kiểm tra biên mảng hai chiều, Thảnh gặp sự cố xóa nhầm cả viền tường và dồn hàng bị sai lệch. Trong nỗ lực sửa lỗi, SV2 đã tạo liên tiếp nhiều branch và commit dồn dập (`e893f4f`, `24f087a`, `1782e60`, `81ee914`, `72a1130`, `e2fdc19`, `5b8396c`, `b9391f9`) cùng các Pull Request #3, #4, #5 bị đóng/revert do xung đột và lỗi logic (trong đó PR #5 bị Copilot Code Reviewer cảnh báo lỗi xóa nhầm toàn bộ thư mục `src/`).
  - **SV4 (Trần Công Thịnh):** Hoàn thành hàm xoay khối tại commit `1758d20` và mở Pull Request #6.
  - **SV5 (Phạm Phú Nguyễn Hưng):** Hoàn thiện tính năng tăng tốc độ rơi khối khi ăn dòng tại commits `a98623f`, `60baf55`, `bd2ee2a` (mở PR #1 và PR #2).
* **Vấn đề phát sinh:** Do tất cả thành viên cùng sửa đổi trực tiếp vào các hàm `draw()`, `removeLine()` và mảng `blocks` trong cùng một file duy nhất `main.cpp`, các nhánh bắt đầu bị xung đột hợp nhất (Merge Conflict) nghiêm trọng. PR #6 và các PR tiếp theo bị gắn nhãn cảnh báo đỏ `CONFLICTING` trên GitHub, không thể tự động merge vào `main`.

### 2.3. Giai đoạn 3: Họp khẩn cấp, Tái cấu trúc Modular và Phân chia lại công việc (17/09 - 18/09/2026)
* **Hoạt động thực tế:**
  - Tối ngày 17/09, nhóm trưởng triệu tập cuộc họp đột xuất trên kênh Slack `#tetris-uit-team` để đánh giá rủi ro. Nhóm nhận ra nguyên nhân cốt lõi là thiết kế "God-file" (nhồi nhét tất cả vào `main.cpp`) đang trở thành nút thắt cổ chai làm tê liệt tiến độ.
  - **Quyết định tái cấu trúc:** SV5 (Nguyễn Hưng) đề xuất giải pháp tách module độc lập dạng Header-only (`DropSpeedController.h`, `ColorRenderer.h`). Mỗi tính năng mới sẽ được đóng gói trong file riêng biệt, chỉ giữ lại vòng lặp điều phối chính tại `main.cpp`.
  - **Phân chia lại công việc trên Trello:**
    1. **SV3 (Nguyễn Hoàng Khang):** Hoàn thiện viền vuông và block vuông với ký tự CP437 `(char)219` và `(char)178` (`feature/square-border-block` - commit `63b108c` -> merge qua PR #7 tại commit `e59bf36`). Đồng thời, Khang nhận thêm vai trò **Đồng thẩm định mã nguồn (Co-reviewer)** hỗ trợ Nhóm trưởng kiểm tra chất lượng code.
    2. **SV2 (Lê Vũ Thảnh):** Được nhóm hỗ trợ trực tiếp qua Slack để sửa dứt điểm điều kiện biên `1 <= j < W - 1` tại commit `5dbf4b9` ("Edit removeLine()"), đóng gói lại thành PR #8 sạch sẽ và tự merge thành công vào `main` tại commit `58de5d6`.
    3. **SV5 (Phạm Phú Nguyễn Hưng):** Giải quyết xung đột cục bộ của nhánh `feature/increase-fall-speed` với `main` tại commit `23dbf76` và `6c2aef8` ("fix: resolve conflict with main"), merge thành công PR #1 tại commit `0a43567`.
    4. **SV1 (Nguyễn Ngọc Duy):** Viết lại tài liệu `README.md` sinh động trên nhánh `chore/readme` (commit `48e34cd`), merge qua PR #10 (commit `bbb7863`).

### 2.4. Giai đoạn 4: Giải quyết xung đột, Tích hợp hệ thống và Nghiệm thu PR (19/09 - 20/09/2026)
* **Hoạt động thực tế:**
  - **Xung đột Merge nhánh Rotate của SV4:** Nhánh `feature/add-function-rotate` của Thịnh bị xung đột nghiêm trọng do `main` đã merge liên tiếp 4 PR (#7, #8, #1, #10). SV4 Thịnh tiến hành pull `main` về nhánh, tự giải quyết xung đột bằng tay tại commit `7dbbd03` ("fix conflict") và cập nhật README tại commit `b78fd52`. PR #6 được đưa về trạng thái Clean và nhóm trưởng Duy merge vào `main` tại commit `839db64`.
  - **Xung đột Merge nhánh HUD Màu sắc của SV5:** Ngay sau khi PR #6 vừa merge, SV5 Hưng mở nhánh `feature/hung-color-theme-ui` (commit `e2a55b2`). Việc thay đổi đồng thời hàm vẽ và hàm xoay gây ra xung đột mới. Hưng thực hiện commit merge `48736da` ("chore: resolve merge conflict with origin/main (integrate rotate and colored UI HUD)"), kiểm tra hiển thị đồng bộ cả xoay khối và màu sắc ANSI, Ghost Piece, Hold Piece, Next Queue. Duy tiến hành review và merge PR #11 vào `main` tại commit `eab7383`.

### 2.5. Giai đoạn 5: Đa nền tảng, Đột phá Refactor OOP toàn diện và Kiểm thử (21/09/2026)
* **Hoạt động thực tế:**
  - **Mở rộng Đa nền tảng (SV1 Duy):** Nhóm trưởng Duy tạo nhánh `feat/platform`, triển khai file trừu tượng hóa [Platform.h](file:///d:/06-Learning/uit-cntt\HK03_2025_2026\SS004-ky-nang-nghe-nghiep\Tetris_UIT\Platform.h) tương thích đồng thời Windows Console API và POSIX `termios` (macOS/Linux), kèm script tự động chạy [play.sh](file:///d:/06-Learning/uit-cntt\HK03_2025_2026\SS004-ky-nang-nghe-nghiep\Tetris_UIT\play.sh) (commit `222ff2c`), merge thành công qua PR #12 tại commit `cd492e7` (HEAD của `main`).
  - **Nâng cấp Điều tốc & Kiểm thử tự động (SV5 Hưng):** Hưng tạo nhánh `feature/hung-increase-fall-speed`, hoàn thiện module [DropSpeedController.h](file:///d:/06-Learning/uit-cntt\HK03_2025_2026\SS004-ky-nang-nghe-nghiep\Tetris_UIT\DropSpeedController.h) với cơ chế Combo Streak, Level và điểm số thưởng (commit `5f22ffc`, `160e248`); bổ sung bộ Unit Test toàn diện [test_speed.cpp](file:///d:/06-Learning/uit-cntt\HK03_2025_2026\SS004-ky-nang-nghe-nghiep\Tetris_UIT\test_speed.cpp) (commit `5280302`, 6/6 tests PASS); cập nhật tài liệu kỹ thuật và hỗ trợ test runner trong `Play_Game.bat` (commits `536a190`, `6648e49`), merge vào `main` qua PR #9 tại commit `d32504c`.
  - **Đột phá Refactor OOP Toàn Diện (SV3 Khang):** 
    Sau khi các tính năng tích hợp ổn định trên `main`, SV3 Khang thực hiện một bước nhảy vọt về mặt kiến trúc phần mềm: phân nhánh trực tiếp từ HEAD `cd492e7` để chuyển đổi toàn bộ mã nguồn sang kiến trúc Hướng đối tượng thuần túy với **14 commits chất lượng cao**:
    1. *Nhánh `refactor/core-classes-khang`:* Khang tách các lớp lõi `Tetromino` (commit `ca0416b`, `d062908`, `3ca6c4f`), `Board` đóng gói mảng `grid` (commit `7d66225`, `d2567fc`), `Bag7` sinh khối ngẫu nhiên chuẩn 7-bag (commit `1c3375f`), chú thích tiếng Việt chuẩn OOP (commit `9aa2b17`).
    2. *Nhánh `refactor/game-states-khang`:* Khang xây dựng tiếp lớp `Renderer` (commit `f773c30`), `Input` (commit `c1cf863`), `Game` điều phối game loop (commit `ffb5a13`), áp dụng State Pattern qua lớp trừu tượng `GameState` và 3 trạng thái `PlayingState`, `PausedState`, `GameOverState` (commit `73b35da`), hoàn thiện phím P/R (commit `906f3b7`, `2bfd916`), rút gọn file `main.cpp` từ ~550 dòng xuống đúng 17 dòng.
  - **Đồng bộ nhánh (SV2 Thảnh):** Thảnh kéo toàn bộ code mới nhất của `main` về nhánh `feature/remove-line` tại commit `8284f43` ("Copy from main") để đảm bảo không bị phân mảnh mã nguồn.

---

## III. CÁC KHÓ KHĂN THỰC TẾ ĐÃ GẶP VÀ CÁCH NHÓM GIẢI QUYẾT

Trong suốt quá trình triển khai, nhóm đã đối mặt và vượt qua 5 khó khăn kỹ thuật và quy trình lớn:

### 3.1. Khó khăn 1: Xung đột mã nguồn nghiêm trọng và Quy trình giải quyết thực tế
* **Biểu hiện:** Khi SV4 (Thịnh) và SV5 (Hưng) cùng nộp PR sau khi SV3 (Khang) và SV2 (Thảnh) đã merge vào `main`, GitHub báo trạng thái `This branch has conflicts that must be resolved`. File `main.cpp` xuất hiện hàng loạt thẻ xung đột `<<<<<<< HEAD`, `=======`, `>>>>>>>` ở các hàm vẽ `draw()`, cấu trúc mảng `blocks` và vòng lặp `while(true)`.
* **Cách giải quyết:**
  - Nhóm kiên quyết không giải quyết conflict trực tiếp trên giao diện web GitHub (vì rất dễ gây sai sót cú pháp C++).
  - Áp dụng nguyên tắc: Thành viên sở hữu nhánh phải kéo `main` mới nhất về máy cục bộ bằng lệnh:
    ```powershell
    git fetch origin
    git merge origin/main
    ```
  - Mở VS Code để trực tiếp so sánh (Side-by-side Diff), giải quyết dứt điểm:
    + **Xung đột nhánh Rotate của SV4:** Thịnh giải quyết tại commit `7dbbd03`, bảo toàn cả hàm xóa hàng mới của Thảnh, viền vuông của Khang và logic xoay khối mới.
    + **Xung đột nhánh HUD Màu sắc của SV5:** Hưng giải quyết tại commit `48736da`, tích hợp liền mạch hàm xoay mới của Thịnh với giao diện vẽ màu ANSI và HUD 3 khung.
  - Về dài hạn, nhóm chuyển dịch sang kiến trúc **Modular Header-only** (`DropSpeedController.h`, `ColorRenderer.h`, `Platform.h`), và đỉnh cao là kiến trúc OOP 7 class của Khang, giúp cách ly các vùng mã nguồn và triệt tiêu xung đột.

### 3.2. Khó khăn 2: Lỗi thuật toán kiểm tra biên và lệch tọa độ dồn hàng trong `removeLine()`
* **Biểu hiện:** Ban đầu hàm `removeLine()` của SV2 duyệt vòng lặp kiểm tra hàng đầy từ `j = 0` đến `j < W`. Do cột `0` và cột `W - 1` là viền tường cố định (chứa ký tự tường), logic đếm ô bị sai hoàn toàn khiến các hàng đầy không bao giờ bị xóa, hoặc khi xóa thì làm biến mất luôn cả hai bờ tường bảo vệ. Ngoài ra, khi xóa một hàng, các hàng phía trên không được dịch chuyển xuống một cách nhịp nhàng.
* **Cách giải quyết:**
  - SV1 Duy và SV5 Hưng tổ chức một buổi gọi thoại chia sẻ màn hình (Screen Sharing) trên Slack với SV2 Thảnh để debug từng bước biến đếm.
  - Hiệu chỉnh lại cận lặp chuẩn: chỉ duyệt trong vùng lòng bàn chơi `1 <= j < W - 1`.
  - Khi phát hiện một dòng $i$ được lấp đầy, thực hiện dịch chuyển từng dòng từ $i$ ngược về dòng $1$ bằng lệnh gán `board[k][j] = board[k-1][j]`, đồng thời khởi tạo lại dòng trên cùng $0$ thành các ô trống. Kết quả được kiểm chứng thực tế tại commit `5dbf4b9` và merge thành công tại PR #8 (commit `58de5d6`).

### 3.3. Khó khăn 3: Hiện tượng chớp giật màn hình (Screen Flickering) và hạn chế của `system("cls")`
* **Biểu hiện:** Phiên bản ban đầu sử dụng lệnh `system("cls")` sau mỗi vòng lặp game để xóa màn hình và vẽ lại frame mới. Khi tốc độ rơi của khối tăng dần lên mức 100ms/ô, màn hình console bị giật và nhấp nháy liên tục với tần số cao, gây mỏi mắt nghiêm trọng và khiến phím bấm phản hồi không ổn định.
* **Cách giải quyết:**
  - SV5 Hưng nghiên cứu giải pháp thay thế lệnh gọi hệ điều hành bằng **Windows Console API cấp thấp**.
  - Trong module `ColorRenderer.h`, nhóm thay thế hoàn toàn `system("cls")` bằng hàm di chuyển con trỏ vẽ về gốc tọa độ:
    ```cpp
    void gotoxy(short x, short y) {
        COORD pos = { x, y };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    }
    ```
  - Đồng thời thiết lập ẩn con trỏ nhấp nháy của console bằng `SetConsoleCursorInfo`. Nhờ đó, hình ảnh bàn cờ được vẽ đè mượt mà trực tiếp lên bộ đệm mà không hề có độ trễ hay chớp giật (Flicker-Free Console Rendering), mang lại trải nghiệm đạt tốc độ khung hình 30 FPS.

### 3.4. Khó khăn 4: Khối gạch bị văng ra ngoài biên tường hoặc đè khối khác khi xoay
* **Biểu hiện:** Khi người chơi di chuyển khối chữ I hoặc chữ L sát mép tường trái/phải rồi nhấn phím xoay `W`, khối bị xoay đè xuyên qua tường ngoài hoặc nhảy vào các khối gạch đã cố định trước đó, làm sai lệch cấu trúc dữ liệu bàn cờ.
* **Cách giải quyết:**
  - SV4 Thịnh phối hợp cùng nhóm xây dựng hàm kiểm tra hợp lệ `canMove()` và kiểm tra vị trí xoay hợp lệ.
  - Tích hợp kỹ thuật **Wall-Kick cơ bản**: Khi vị trí xoay mới bị chạm tường, hệ thống sẽ tự động thử dịch chuyển khối sang trái hoặc sang phải 1 ô. Nếu vị trí dịch chuyển hợp lệ, hệ thống chấp nhận hướng xoay; nếu cả hai phía đều bị chắn, lệnh xoay sẽ bị hủy bỏ (giữ nguyên trạng thái xoay cũ) để đảm bảo khối không bao giờ vượt qua phạm vi an toàn. Sau này được Khang hoàn thiện thành phương thức bất biến `Tetromino::rotated() const` trả về bản sao an toàn.

### 3.5. Khó khăn 5: Lệch pha múi giờ sinh hoạt và nguy cơ trễ hạn chót (Deadline)
* **Biểu hiện:** Một số thành viên có lịch học và thói quen sinh hoạt khác nhau, dẫn đến tình trạng tin nhắn trên Slack không được phản hồi kịp thời, các PR mở ra nằm chờ duyệt hàng ngày trời mà không ai review, làm chậm tiến độ chung.
* **Cách giải quyết:**
  - Nhóm bổ sung **Điều khoản phản hồi** vào thỏa thuận làm việc: Tất cả thành viên phải cài đặt ứng dụng Slack trên điện thoại và phản hồi thông báo khẩn cấp trong vòng tối đa 4 giờ.
  - Phân quyền thêm cho SV3 Khang làm Co-reviewer để tránh trường hợp chỉ phụ thuộc duy nhất vào Nhóm trưởng.
  - Trên Trello, nhóm trưởng gán nhãn màu vàng/đỏ (Due Date Warning) cho các thẻ có thời hạn dưới 48 giờ. Thẻ nào sắp đến hạn sẽ được đưa lên ưu tiên thảo luận hàng đầu trong phiên Standup mỗi sáng.

---

## IV. PHÂN CHIA VÀ PHÂN CHIA LẠI CÔNG VIỆC CỦA CÁC THÀNH VIÊN

Sự thành công của dự án xuất phát từ sự linh hoạt trong quản trị: **không áp đặt cứng nhắc bảng phân công ban đầu mà sẵn sàng điều chỉnh dựa trên tình hình thực tế và năng lực chuyên sâu của từng cá nhân**.

### 4.1. Bảng đối chiếu phân công công việc: Ban đầu vs. Thực tế (Kèm Dẫn chứng Git)

| Thành viên (MSSV) | Phân công ban đầu (Tuần 1) | Điều chỉnh & Phân chia lại thực tế (Tuần 2 - 3) | Kết quả cụ thể & Dẫn chứng Git (Commit / PR) |
| :--- | :--- | :--- | :--- |
| **Nguyễn Ngọc Duy**<br>*(26730013 - SV1)* | - Khởi tạo repo<br>- Quản trị Git & Merge PR<br>- Quản lý thẻ Trello | - Giữ vai trò Trưởng nhóm (PM), điều phối dự án<br>- Thiết lập kỷ luật bảo vệ nhánh `main`<br>- Trực tiếp hỗ trợ SV2 gỡ lỗi logic xóa hàng<br>- Viết lại `README.md` chuyên nghiệp<br>- **Mở rộng**: Viết giải pháp đa nền tảng Windows + Linux/macOS | - **10 commits, 2 PRs Merged (#10, #12)**<br>- Commit `a311e39`, `b1f6d45` (tạo repo, code ban đầu)<br>- Commit `dc56b3f` (revert bảo vệ `main`)<br>- Commit `48e34cd`, PR #10 (cập nhật README)<br>- Commit `222ff2c`, PR #12 (`Platform.h`, `play.sh`) |
| **Lê Vũ Thảnh**<br>*(26730061 - SV2)* | - Viết hàm `removeLine()` xóa hàng khi đầy | - Được nhóm tinh giản phạm vi: tập trung hoàn thiện chính xác logic mảng của `removeLine()`<br>- Chuyển giao phần hiệu ứng rơi cho SV5<br>- Đồng bộ nhánh với mã nguồn `main` mới nhất | - **12 commits, 1 PR Merged (#8), 3 PRs Closed (#3, #4, #5)**<br>- Commits `e893f4f`, `24f087a`, `1782e60`, `81ee914` (chuỗi commit tìm lỗi)<br>- Commit `5dbf4b9` ("Edit removeLine()" chuẩn xác)<br>- Commit `58de5d6` (Merge PR #8 vào `main`)<br>- Commit `8284f43` ("Copy from main" đồng bộ nhánh) |
| **Nguyễn Hoàng Khang**<br>*(26730030 - SV3)* | - Vẽ viền bàn cờ và khối gạch vuông | - Hoàn thành giao diện viền khối ký tự CP437<br>- **Bổ sung vai trò Co-reviewer**: thẩm định chéo các PR #6, #8, #11 cùng Trưởng nhóm<br>- **Đột phá vai trò Kiến trúc sư OOP**: Tự chủ refactor 100% game sang 7 lớp đối tượng chuẩn mực | - **16 commits, 1 PR Merged (#7) & 14 commits Refactor OOP**<br>- Commit `63b108c`, PR #7 (`e59bf36`: viền khối vuông CP437)<br>- Nhánh `refactor/core-classes-khang`: commits `61eb4d6`, `ca0416b` (`Tetromino`), `7d66225` (`Board`), `1c3375f` (`Bag7`), `9aa2b17`<br>- Nhánh `refactor/game-states-khang`: commits `f773c30` (`Renderer`), `c1cf863` (`Input`), `ffb5a13` (`Game`), `73b35da` (`GameState`), `2bfd916` (rút gọn `main.cpp` còn 17 dòng) |
| **Trần Công Thịnh**<br>*(26730064 - SV4)* | - Viết hàm xoay khối gạch `rotate()` | - Hoàn thành hàm xoay ma trận<br>- **Nhận thêm nhiệm vụ tự rebase và giải quyết merge conflict cục bộ với `main`**<br>- Thêm cơ chế chống kẹt tường (Wall-Kick cơ bản) | - **4 commits, 1 PR Merged (#6)**<br>- Commit `1758d20` ("Add function rotate")<br>- **Commit `7dbbd03` ("fix conflict")**: tự tay giải quyết xung đột code với nhánh `main`<br>- Commit `b78fd52` (cập nhật README hướng dẫn phím W)<br>- Merge PR #6 vào `main` tại commit `839db64` |
| **Phạm Phú Nguyễn Hưng**<br>*(26730023 - SV5)* | - Viết tính năng tăng tốc độ rơi `DropSpeedController` | - Hoàn thành `DropSpeedController.h`<br>- **Nhận thêm khối lượng công việc mở rộng (Báo cáo 3.3)**: Thiết kế toàn bộ HUD màu sắc ANSI, Flicker-Free, Ghost Piece, Hold Piece, Next Queue<br>- **Tự giải quyết xung đột tích hợp (PR #1, PR #11)**<br>- **Xây dựng bộ kiểm thử tự động Unit Test** và tài liệu báo cáo | - **15 commits, 3 PRs Merged (#1, #9, #11), 1 PR Closed (#2)**<br>- Commit `a98623f`, PR #1 (tăng tốc độ rơi)<br>- **Commit `23dbf76`, `6c2aef8` (resolve conflict PR #1)**<br>- Commit `e2a55b2`, PR #11 (HUD màu ANSI, Ghost, Hold, Next)<br>- **Commit `48736da` (resolve conflict PR #11 với rotate của Thịnh)**<br>- Commit `5f22ffc`, `160e248`, `5280302` (Unit Test `test_speed.cpp` 6/6 tests PASS), `6648e49`, PR #9 (`d32504c`) |

### 4.2. Bảng tổng hợp các sự kiện Xung đột mã nguồn (Merge Conflicts) và Cách thức giải quyết

| Mã Xung đột | Nhánh / PR liên quan | Nguyên nhân xung đột | Thành viên xử lý | Commit minh chứng giải quyết | Kết quả kỹ thuật |
| :---: | :--- | :--- | :--- | :--- | :--- |
| **CFL-01** | `main` (15/09) | SV2 Thảnh push trực tiếp commit `d050f29` lên nhánh `main`, vi phạm quy chuẩn Git Flow | SV1 Duy (PM) | Commit `dc56b3f` (`Revert "First commit"`) | Nhánh `main` được khôi phục an toàn, thiết lập kỷ luật bắt buộc làm việc qua feature branch và PR |
| **CFL-02** | `feature/increase-fall-speed` (PR #1 - 18/09) | Nhánh tăng tốc của Hưng phân nhánh từ commit cũ (`a311e39`), bị lệch cấu trúc sau khi `main` đã merge viền vuông (#7) và xóa hàng (#8) | SV5 Hưng | Commits `23dbf76` và `6c2aef8` ("fix: resolve conflict with main") | Hưng pull `main` về nhánh con, ghép nối logic tăng tốc rơi mà không ghi đè viền vuông và hàm xóa dòng; PR #1 merge sạch qua commit `0a43567` |
| **CFL-03** | `feature/add-function-rotate` (PR #6 - 19/09) | Nhánh xoay của Thịnh tạo từ ngày 16/09; trong lúc đó `main` đã lần lượt merge PR #7, #8, #1, #10 khiến toàn bộ hàm vẽ `draw()` và `main()` bị lệch dòng | SV4 Thịnh | **Commit `7dbbd03` ("fix conflict")** | Thịnh tự fetch `main` về máy, mở diff giải quyết xung đột thủ công, giữ nguyên các tính năng của đồng đội và bổ sung hàm `rotate()`; PR #6 merge qua commit `839db64` |
| **CFL-04** | `feature/hung-color-theme-ui` (PR #11 - 19/09) | Nhánh giao diện màu của Hưng phát triển song song với nhánh xoay của Thịnh. Khi PR #6 của Thịnh vừa merge vào `main`, nhánh của Hưng bị conflict ở các phím bấm và hàm vẽ | SV5 Hưng | **Commit `48736da` ("chore: resolve merge conflict with origin/main")** | Hưng đồng bộ nhánh, tích hợp phím xoay `W` của Thịnh vào giao diện màu sắc ANSI mới, kiểm tra không lỗi trước khi merge qua PR #11 (commit `eab7383`) |

### 4.3. Phân tích nguyên nhân và hiệu quả của việc phân chia lại công việc
1. **Tránh quá tải và giải phóng điểm nghẽn (Unblocking Bottlenecks):** Việc hỗ trợ SV2 gỡ lỗi mảng biên đã giải phóng nhánh `feature/remove-line` bị kẹt suốt 3 ngày, giúp các tính năng khác tiếp tục được ráp nối vào `main`.
2. **Tận dụng tối đa thế mạnh cá nhân:** 
   - SV5 Hưng có kinh nghiệm chuyên sâu về kiến trúc hệ thống và Windows Console API nên việc giao thêm toàn bộ phần đồ họa, màu sắc, cơ chế Flicker-Free và kiểm thử tự động cho SV5 đã nâng tầm trò chơi từ một bài thực hành thô sơ thành một sản phẩm hoàn chỉnh, trực quan.
   - SV3 Khang thể hiện năng lực kiến trúc phần mềm xuất sắc khi chủ động đảm nhận trọng trách Refactor toàn diện sang OOP, biến mã nguồn từ dạng thủ tục sơ khai thành kiến trúc 7 lớp hướng đối tượng mẫu mực.
3. **Phân tán quyền lực xét duyệt:** Việc bổ sung SV3 Khang làm reviewer thứ hai đã giảm tải 50% áp lực xét duyệt cho Nhóm trưởng Duy, giúp tốc độ phản hồi và merge PR tăng gấp đôi.

---

## V. ĐÁNH GIÁ MỨC ĐỘ ĐÓNG GÓP VÀ BÀI HỌC KINH NGHIỆM

### 5.1. Bảng tổng kết đánh giá mức độ đóng góp cá nhân (Dữ liệu SSOT từ Git)

| STT | Thành viên | MSSV | Vai trò chính | Minh chứng định lượng trên Git / Trello | Tỷ lệ đóng góp | Xếp loại nội bộ |
| :---: | :--- | :---: | :--- | :--- | :---: | :---: |
| 1 | **Nguyễn Ngọc Duy** | 26730013 | Trưởng nhóm, Quản trị Trello/Git, Kiến trúc Đa nền tảng | **10 commits, 2 PRs Merged (#10, #12)**, revert bảo vệ main (`dc56b3f`), tạo `Platform.h` và `play.sh`, hoàn thiện README | **100%** | Xuất sắc |
| 2 | **Lê Vũ Thảnh** | 26730061 | Phát triển thuật toán xóa hàng `removeLine()` | **12 commits, 1 PR Merged (#8), 3 PRs Closed (#3, #4, #5)**, kiên trì khắc phục lỗi biên mảng sau 4 vòng lặp | **100%** | Hoàn thành tốt |
| 3 | **Nguyễn Hoàng Khang** | 26730030 | Thiết kế viền khối vuông, Co-reviewer, Kiến trúc sư Refactor OOP | **16 commits, 1 PR Merged (#7)**, **14 commits Refactor OOP** tách 7 class (`Tetromino`, `Board`, `Bag7`, `Renderer`, `Input`, `Game`, `GameState`), rút gọn `main.cpp` còn 17 dòng | **100%** | Xuất sắc |
| 4 | **Trần Công Thịnh** | 26730064 | Phát triển giải thuật xoay khối gạch `rotate()` | **4 commits, 1 PR Merged (#6)**, chủ động giải quyết merge conflict cục bộ tại commit `7dbbd03` | **100%** | Hoàn thành tốt |
| 5 | **Phạm Phú Nguyễn Hưng** | 26730023 | Kiến trúc module, HUD màu sắc, Flicker-Free, Điều tốc & Unit Test | **15 commits, 3 PRs Merged (#1, #9, #11), 1 PR Closed (#2)**, giải quyết conflict `48736da`, viết 6 unit test cases `test_speed.cpp` (100% PASS), biên tập tài liệu nhóm | **100%** | Xuất sắc |

### 5.2. Các bài học kinh nghiệm cốt lõi (Lessons Learned)

#### Về mặt Kỹ thuật (Technical Lessons)
1. **Kiến trúc hướng đối tượng và module hóa (OOP & Modular Architecture):** Tuyệt đối không nhồi nhét tất cả logic vào một file nguồn duy nhất. Việc chuyển dịch từ procedural sang các lớp đối tượng có tính đóng gói cao (`Board`, `Tetromino`, `DropSpeedController`) và State Pattern là chìa khóa vàng để các thành viên code song song mà không dẫm chân lên nhau.
2. **Kỷ luật Git Flow nghiêm ngặt:** Luôn tuân thủ quy trình `git fetch` và `git merge origin/main` cục bộ trước khi push. Không bao giờ merge PR khi chưa biên dịch kiểm tra tính đúng đắn trên máy tính cá nhân.
3. **Cơ chế xét duyệt chéo (Mandatory Code Review):** Quy định bắt buộc có 2 reviewers (Duy và Khang) đã giúp phát hiện sớm các lỗi lệch chỉ số mảng và rò rỉ bộ nhớ trước khi mã nguồn được tích hợp vào nhánh chính.
4. **Kiểm thử tự động hướng miền (Domain-Driven Unit Testing):** Test pass thôi là chưa đủ, mà giá trị input/output phải khớp domain nghiệp vụ. Bộ kiểm thử tự động độc lập (`test_speed.cpp`) giúp đảm bảo cơ chế gia tốc rơi và combo streak vận hành chính xác 100% mà không phụ thuộc vào giao diện đồ họa.

#### Về mặt Kỹ năng nghề nghiệp & Làm việc nhóm (Soft Skills & Teamwork)
1. **Văn hóa giao tiếp chủ động và cởi mở (Psychological Safety):** Khi gặp lỗi kỹ thuật khó khăn (như trường hợp của SV2), sự hỗ trợ tận tình từ đồng đội thay vì chỉ trích đã tạo động lực to lớn giúp thành viên tự tin giải quyết vấn đề.
2. **Minh bạch tiến độ với Kanban:** Bảng Trello được cập nhật hàng ngày giúp mọi thành viên đều nắm rõ dự án đang ở đâu, ai đang làm gì và ai đang cần giúp đỡ, loại bỏ hoàn toàn sự mập mờ trong trách nhiệm.
3. **Linh hoạt và sẵn sàng tái cấu trúc:** Khả năng nhận diện nút thắt sớm và dũng cảm phân chia lại công việc chính là kỹ năng quan trọng nhất giúp nhóm đưa dự án về đích thành công và đúng hạn tuyệt đối.

---
*(Báo cáo được biên soạn và cập nhật dựa trên dữ liệu SSOT Git Repository bởi thành viên Phạm Phú Nguyễn Hưng - Nhóm Hidden Gem, UIT)*
