# -*- coding: utf-8 -*-
import os
import sys
if sys.stdout.encoding != 'utf-8':
    try:
        sys.stdout.reconfigure(encoding='utf-8')
    except Exception:
        pass
import docx
from docx.shared import Inches, Pt, RGBColor
from docx.enum.text import WD_ALIGN_PARAGRAPH
from docx.enum.table import WD_TABLE_ALIGNMENT, WD_ALIGN_VERTICAL
from docx.oxml import parse_xml, OxmlElement
from docx.oxml.ns import nsdecls, qn

def set_cell_background(cell, fill_hex):
    tcPr = cell._tc.get_or_add_tcPr()
    shd = parse_xml(f'<w:shd {nsdecls("w")} w:fill="{fill_hex}"/>')
    tcPr.append(shd)

def set_cell_margins(cell, top=100, bottom=100, left=140, right=140):
    tcPr = cell._tc.get_or_add_tcPr()
    tcMar = parse_xml(f'<w:tcMar {nsdecls("w")}><w:top w:w="{top}" w:type="dxa"/><w:bottom w:w="{bottom}" w:type="dxa"/><w:left w:w="{left}" w:type="dxa"/><w:right w:w="{right}" w:type="dxa"/></w:tcMar>')
    tcPr.append(tcMar)

def set_table_borders(table, color="94A3B8", sz="4", val="single"):
    tblPr = table._tbl.tblPr
    borders = parse_xml(f'''
        <w:tblBorders {nsdecls("w")}>
            <w:top w:val="{val}" w:sz="{sz}" w:space="0" w:color="{color}"/>
            <w:bottom w:val="{val}" w:sz="{sz}" w:space="0" w:color="{color}"/>
            <w:left w:val="none"/>
            <w:right w:val="none"/>
            <w:insideH w:val="{val}" w:sz="{sz}" w:space="0" w:color="{color}"/>
            <w:insideV w:val="none"/>
        </w:tblBorders>
    ''')
    tblPr.append(borders)

def add_callout(doc, title, content, border_color="1D4ED8", bg_color="EFF6FF"):
    tbl = doc.add_table(rows=1, cols=1)
    tbl.alignment = WD_TABLE_ALIGNMENT.CENTER
    tbl.autofit = False
    
    cell = tbl.cell(0, 0)
    cell.width = Inches(6.8)
    set_cell_background(cell, bg_color)
    set_cell_margins(cell, top=120, bottom=120, left=180, right=180)
    
    tcPr = cell._tc.get_or_add_tcPr()
    borders = parse_xml(f'''
        <w:tcBorders {nsdecls("w")}>
            <w:left w:val="single" w:sz="24" w:space="0" w:color="{border_color}"/>
            <w:top w:val="none"/>
            <w:right w:val="none"/>
            <w:bottom w:val="none"/>
        </w:tcBorders>
    ''')
    tcPr.append(borders)
    
    p = cell.paragraphs[0]
    p.paragraph_format.space_before = Pt(2)
    p.paragraph_format.space_after = Pt(3)
    p.paragraph_format.line_spacing = 1.15
    run_t = p.add_run(f"📌 {title}\n")
    run_t.font.name = "Times New Roman"
    run_t.font.size = Pt(11)
    run_t.font.bold = True
    run_t.font.color.rgb = RGBColor(0x1E, 0x3A, 0x8A)
    
    run_c = p.add_run(content)
    run_c.font.name = "Times New Roman"
    run_c.font.size = Pt(10.5)
    run_c.font.italic = False
    run_c.font.color.rgb = RGBColor(0x1E, 0x29, 0x3B)
    
    p_after = doc.add_paragraph()
    p_after.paragraph_format.space_before = Pt(0)
    p_after.paragraph_format.space_after = Pt(4)

def format_row(row, is_header=False, bg_color=None):
    for cell in row.cells:
        cell.vertical_alignment = WD_ALIGN_VERTICAL.CENTER
        if bg_color:
            set_cell_background(cell, bg_color)
        set_cell_margins(cell, top=100, bottom=100, left=120, right=120)
        for p in cell.paragraphs:
            p.paragraph_format.space_before = Pt(2)
            p.paragraph_format.space_after = Pt(2)
            p.paragraph_format.line_spacing = 1.15
            for run in p.runs:
                run.font.name = "Times New Roman"
                if is_header:
                    run.font.bold = True
                    run.font.size = Pt(10.5)
                    run.font.color.rgb = RGBColor(0xFF, 0xFF, 0xFF)
                else:
                    run.font.size = Pt(10)
                    run.font.color.rgb = RGBColor(0x0F, 0x17, 0x2A)

def create_document():
    doc = docx.Document()
    
    # Thiết lập lề trang tiêu chuẩn A4
    for section in doc.sections:
        section.top_margin = Inches(0.8)
        section.bottom_margin = Inches(0.8)
        section.left_margin = Inches(0.9)
        section.right_margin = Inches(0.8)
        
        # Header / Footer
        header = section.header
        p_hdr = header.paragraphs[0]
        p_hdr.alignment = WD_ALIGN_PARAGRAPH.RIGHT
        r_hdr = p_hdr.add_run("UIT - SS004: Kỹ năng nghề nghiệp | Báo cáo Quá trình Làm việc Nhóm")
        r_hdr.font.name = "Times New Roman"
        r_hdr.font.size = Pt(9)
        r_hdr.font.italic = True
        r_hdr.font.color.rgb = RGBColor(0x64, 0x74, 0x8B)

    # 1. Header cơ quan & Tiêu đề chính
    p_top = doc.add_paragraph()
    p_top.alignment = WD_ALIGN_PARAGRAPH.CENTER
    p_top.paragraph_format.space_before = Pt(0)
    p_top.paragraph_format.space_after = Pt(2)
    r1 = p_top.add_run("ĐẠI HỌC QUỐC GIA TP. HỒ CHÍ MINH\nTRƯỜNG ĐẠI HỌC CÔNG NGHỆ THÔNG TIN\n")
    r1.font.name = "Times New Roman"
    r1.font.size = Pt(11)
    r1.font.bold = True
    r1.font.color.rgb = RGBColor(0x1E, 0x3A, 0x8A)
    
    r2 = p_top.add_run("KHOA CÔNG NGHỆ THÔNG TIN — MÔN HỌC KỸ NĂNG NGHỀ NGHIỆP (SS004)\n")
    r2.font.name = "Times New Roman"
    r2.font.size = Pt(10.5)
    r2.font.bold = True
    r2.font.color.rgb = RGBColor(0x47, 0x55, 0x69)
    
    p_title = doc.add_paragraph()
    p_title.alignment = WD_ALIGN_PARAGRAPH.CENTER
    p_title.paragraph_format.space_before = Pt(8)
    p_title.paragraph_format.space_after = Pt(4)
    r_t = p_title.add_run("BÁO CÁO CHUYÊN ĐỀ LÀM VIỆC NHÓM\nMÔ TẢ QUÁ TRÌNH LÀM VIỆC NHÓM TRONG DỰ ÁN TETRIS_UIT")
    r_t.font.name = "Times New Roman"
    r_t.font.size = Pt(14)
    r_t.font.bold = True
    r_t.font.color.rgb = RGBColor(0x0F, 0x17, 0x2A)

    # Thông tin nhanh về bài nộp
    add_callout(doc, "THÔNG TIN BÀI BÁO CÁO & THẺ CÔNG VIỆC TRELLO",
                "• Lớp học phần: SS004.F31.CN1.CNTT | Giảng viên hướng dẫn: ThS. Nguyễn Văn Toàn (toannv@uit.edu.vn)\n"
                "• Tên nhóm: Hidden Gem (Nhóm Tetris_UIT) | Mã nguồn GitHub: github.com/26730013-NguyenNgocDuy/Tetris_UIT\n"
                "• Người thực hiện: Phạm Phú Nguyễn Hưng (MSSV: 26730023 - SV5)\n"
                "• Thẻ Trello phụ trách: 'Mô tả quá trình làm việc nhóm' (Nhãn: Report, Hạn chót: 12:00 ngày 21/09/2026)\n"
                "• Quy cách: Dựa trên lịch sử thực tế Trello/Git/Slack, nêu rõ các giai đoạn, khó khăn, giải quyết, phân chia và phân chia lại công việc. Độ dài: 4 trang chuẩn A4 (Đáp ứng quy định 2-5 trang).")

    def add_h1(text):
        p = doc.add_paragraph()
        p.paragraph_format.space_before = Pt(12)
        p.paragraph_format.space_after = Pt(4)
        p.paragraph_format.keep_with_next = True
        r = p.add_run(text)
        r.font.name = "Times New Roman"
        r.font.size = Pt(12.5)
        r.font.bold = True
        r.font.color.rgb = RGBColor(0x1E, 0x3A, 0x8A)

    def add_h2(text):
        p = doc.add_paragraph()
        p.paragraph_format.space_before = Pt(8)
        p.paragraph_format.space_after = Pt(3)
        p.paragraph_format.keep_with_next = True
        r = p.add_run(text)
        r.font.name = "Times New Roman"
        r.font.size = Pt(11.5)
        r.font.bold = True
        r.font.color.rgb = RGBColor(0x0F, 0x17, 0x2A)

    def add_body(text, bold_prefix=None):
        p = doc.add_paragraph()
        p.paragraph_format.space_before = Pt(2)
        p.paragraph_format.space_after = Pt(3)
        p.paragraph_format.line_spacing = 1.15
        p.alignment = WD_ALIGN_PARAGRAPH.JUSTIFY
        if bold_prefix:
            rb = p.add_run(bold_prefix)
            rb.font.name = "Times New Roman"
            rb.font.size = Pt(11)
            rb.font.bold = True
            rb.font.color.rgb = RGBColor(0x0F, 0x17, 0x2A)
        r = p.add_run(text)
        r.font.name = "Times New Roman"
        r.font.size = Pt(11)
        r.font.color.rgb = RGBColor(0x1E, 0x29, 0x3B)
        return p

    def add_bullet(text, bold_prefix=None):
        p = doc.add_paragraph(style='List Bullet')
        p.paragraph_format.space_before = Pt(1)
        p.paragraph_format.space_after = Pt(2)
        p.paragraph_format.line_spacing = 1.15
        p.alignment = WD_ALIGN_PARAGRAPH.JUSTIFY
        if bold_prefix:
            rb = p.add_run(bold_prefix)
            rb.font.name = "Times New Roman"
            rb.font.size = Pt(10.5)
            rb.font.bold = True
            rb.font.color.rgb = RGBColor(0x0F, 0x17, 0x2A)
        r = p.add_run(text)
        r.font.name = "Times New Roman"
        r.font.size = Pt(10.5)
        r.font.color.rgb = RGBColor(0x1E, 0x29, 0x3B)
        return p

    # ================= I. TỔNG QUAN DỰ ÁN & MÔI TRƯỜNG CỘNG TÁC SỐ =================
    add_h1("I. TỔNG QUAN DỰ ÁN VÀ THIẾT LẬP MÔI TRƯỜNG CỘNG TÁC SỐ")
    add_body("Trong khuôn khổ học phần Kỹ năng nghề nghiệp (SS004), nhóm Hidden Gem nhận nhiệm vụ xây dựng trò chơi xếp gạch cổ điển Console C++ Tetris_UIT. Trọng tâm của đồ án là rèn luyện và chuẩn hóa kỹ năng làm việc nhóm song song trên các nền tảng số hóa theo mô hình Agile/Scrum. Dự án đòi hỏi 5 thành viên phải phối hợp nhịp nhàng, phân chia chức năng độc lập, quản lý tiến độ minh bạch và trực tiếp đối mặt, xử lý các tình huống xung đột mã nguồn (Git Merge Conflicts) thực tế phát sinh trong môi trường phát triển phần mềm chuyên nghiệp.")
    
    add_h2("1.1. Các công cụ cộng tác trực tuyến đã thiết lập")
    add_bullet(" Nơi lưu trữ tập trung toàn bộ mã nguồn của dự án. Nhóm áp dụng quy tắc phân nhánh tính năng (Feature Branching), bảo vệ nhánh chính và tuyệt đối không push thẳng lên origin/main.", "• GitHub Repository: ")
    add_bullet(" Bảng Kanban số hóa theo dõi trạng thái nhiệm vụ gồm 4 cột: To Do, In Progress, Review/Testing và Completed. Mỗi thẻ đều được gán nhãn nhận diện (Report, Feature, Bugfix), quy định thời hạn nộp (Due date) và phân công thành viên phụ trách rõ ràng.", "• Trello Workspace: ")
    add_bullet(" Kênh trao đổi công khai ss004f31.slack.com (#tetris-uit-team) dùng cho các cuộc họp nhanh (Standup), gỡ lỗi thời gian thực và tích hợp GitHub bot tự động gửi thông báo khi có commit hoặc Pull Request mới.", "• Slack Channel: ")

    add_h2("1.2. Phân công công việc ban đầu giữa 5 thành viên")
    add_body("Dựa trên năng lực chuyên môn và đề xuất ban đầu, Trưởng nhóm Nguyễn Ngọc Duy đã giao việc qua Trello như sau:")
    
    tbl1 = doc.add_table(rows=6, cols=4)
    tbl1.alignment = WD_TABLE_ALIGNMENT.CENTER
    set_table_borders(tbl1)
    
    headers1 = ["STT", "Thành viên", "MSSV", "Nhiệm vụ ban đầu được giao"]
    for i, h in enumerate(headers1):
        tbl1.cell(0, i).paragraphs[0].text = h
    format_row(tbl1.rows[0], is_header=True, bg_color="1E3A8A")
    
    data1 = [
        ("SV1", "Nguyễn Ngọc Duy (Trưởng nhóm)", "26730013", "Khởi tạo repo, thiết kế khung main.cpp, quản trị Trello, review & merge PR."),
        ("SV2", "Lê Vũ Thảnh", "26730061", "Viết thuật toán xóa hàng khi đầy removeLine() (nhánh feature/remove-line)."),
        ("SV3", "Nguyễn Hoàng Khang", "26730030", "Thiết kế viền bàn cờ và khối gạch vuông ký tự đặc biệt (feature/square-border-block)."),
        ("SV4", "Trần Công Thịnh", "26730064", "Viết giải thuật xoay khối Tetromino rotate() (feature/add-function-rotate)."),
        ("SV5", "Phạm Phú Nguyễn Hưng", "26730023", "Viết cơ chế tăng dần tốc độ rơi sau khi ăn dòng DropSpeedController.h.")
    ]
    
    for row_idx, row_data in enumerate(data1, start=1):
        bg = "F8FAFC" if row_idx % 2 == 1 else "FFFFFF"
        for col_idx, val in enumerate(row_data):
            tbl1.cell(row_idx, col_idx).paragraphs[0].text = val
        format_row(tbl1.rows[row_idx], is_header=False, bg_color=bg)

    # ================= II. CÁC GIAI ĐOẠN TRIỂN KHAI THỰC TẾ =================
    add_h1("II. CÁC GIAI ĐOẠN TRIỂN KHAI THỰC TẾ (TIMELINE & PHASES)")
    add_body("Dựa trên nhật ký commit thực tế trên GitHub và lịch sử trao đổi trên Slack/Trello, dự án đã trải qua 5 giai đoạn phát triển rõ rệt:")

    add_h2("2.1. Giai đoạn 1: Khởi động và Dựng khung sườn cơ bản (Ngày 14/09/2026)")
    add_bullet("Trưởng nhóm Duy khởi tạo repo, đẩy mã nguồn ban đầu qua các commit a311e39, b1f6d45 và cập nhật README qua bb5de88.")
    add_bullet("Họp trực tuyến phiên đầu trên Slack, nhóm thống nhất giữ cấu trúc ban đầu trong một file main.cpp để đơn giản hóa quá trình chạy thử nghiệm ban đầu.")

    add_h2("2.2. Giai đoạn 2: Phát triển song song và Khủng hoảng Merge Conflict đầu tiên (15/09 - 16/09/2026)")
    add_bullet("Các thành viên tạo nhánh cá nhân và bắt đầu code độc lập. SV2 Thảnh push trực tiếp commit d050f29 lên main; Duy revert bằng commit dc56b3f để thiết lập kỷ luật Git Flow.")
    add_bullet("SV2 Thảnh gặp lỗi mảng biên xóa hàng, tạo hàng loạt commit và các PR #3, #4, #5 phải đóng do lỗi logic (PR #5 bị Copilot cảnh báo xóa nhầm thư mục src/).")
    add_bullet("SV4 Thịnh mở PR #6 (xoay khối); SV5 Hưng mở PR #1 (tăng tốc độ rơi). Tuy nhiên, do tất cả cùng chỉnh sửa trực tiếp vào hàm draw() và mảng blocks trên cùng một file main.cpp, hệ thống GitHub rơi vào tình trạng xung đột nghiêm trọng (Conflicting state), không thể tự động merge.")

    add_h2("2.3. Giai đoạn 3: Họp khẩn Slack, Tái cấu trúc Modular và Phân chia lại công việc (17/09 - 18/09/2026)")
    add_bullet("Nhóm trưởng Duy triệu tập họp khẩn cấp trên Slack ngày 17/09. Nhóm xác định kiến trúc 'God-file' là nguyên nhân cốt lõi gây nghẽn tiến độ.")
    add_bullet("Quyết định kỹ thuật: SV5 Hưng đề xuất tái cấu trúc mã nguồn theo hướng Module hóa Header-only (DropSpeedController.h, ColorRenderer.h) giúp cô lập các tính năng.")
    add_bullet("Phân chia lại công việc: Khang (SV3) nhận thêm vai trò Co-reviewer hỗ trợ Duy; Thảnh (SV2) được hỗ trợ debug dứt điểm logic xóa hàng tại commit 5dbf4b9; Hưng (SV5) nhận thêm trọng trách xây dựng toàn bộ giao diện Console màu sắc, Flicker-Free, Ghost Piece, Hold Piece và Next Queue theo đúng yêu cầu Báo cáo 3.3.")

    add_h2("2.4. Giai đoạn 4: Giải quyết xung đột, Tích hợp tổng thể và Thẩm định đa chiều (19/09 - 20/09/2026)")
    add_bullet("Nhánh viền khối của Khang (PR #7, commit e59bf36) và xóa hàng của Thảnh (PR #8, commit 58de5d6) được merge tuần tự vào main.")
    add_bullet("SV4 Thịnh tự kéo main về máy, giải quyết xung đột cục bộ (commit 7dbbd03 'fix conflict') và PR #6 được merge thành công (commit 839db64).")
    add_bullet("SV5 Hưng kéo main mới nhất về nhánh feature/hung-color-theme-ui, giải quyết xung đột tích hợp giữa rotate và giao diện màu mới (commit 48736da). Sau khi Duy và Khang thẩm định chéo, PR #11 được merge sạch sẽ vào main (commit eab7383).")

    add_h2("2.5. Giai đoạn 5: Đa nền tảng, Đột phá Refactor OOP toàn diện và Kiểm thử (21/09/2026)")
    add_bullet("Trưởng nhóm Duy xây dựng module trừu tượng hóa Platform.h (POSIX termios + Windows API) và script play.sh hỗ trợ macOS/Linux (commit 222ff2c), merge qua PR #12 (commit cd492e7).")
    add_bullet("SV5 Hưng nâng cấp DropSpeedController.h với Combo Streak, Level và xây dựng bộ Unit Test độc lập test_speed.cpp (6/6 tests PASS, commit 5280302), merge qua PR #9 (commit d32504c).")
    add_bullet("Đột phá Refactor OOP của SV3 Khang: Khang phân nhánh từ HEAD của main, thực hiện 14 commits tách 7 lớp đối tượng chuẩn mực (Board, Tetromino, Bag7, Renderer, Input, Game, GameState), áp dụng State Pattern và rút gọn main.cpp từ 550 dòng xuống đúng 17 dòng.")
    add_bullet("Hoàn tất hồ sơ báo cáo nhóm và chuyển toàn bộ thẻ Trello sang cột Completed đúng hạn chót.")

    # ================= III. CÁC KHÓ KHĂN THỰC TẾ & CÁCH GIẢI QUYẾT =================
    add_h1("III. CÁC KHÓ KHĂN THỰC TẾ ĐÃ GẶP VÀ CÁCH GIẢI QUYẾT")
    add_body("Quá trình phát triển đã mang lại nhiều bài học thực tiễn thông qua việc trực tiếp tháo gỡ 5 rào cản kỹ thuật và quy trình:")

    add_h2("3.1. Xung đột mã nguồn nghiêm trọng và Cách giải quyết thực tế qua các Commit")
    add_bullet("Khi 4 thành viên nộp PR cùng lúc, file main.cpp xuất hiện chi chít các điểm xung đột <<<<<<< HEAD và >>>>>>>.", "• Bản chất: ")
    add_bullet("Nhóm giải quyết conflict trực tiếp trên máy cục bộ với các commit minh chứng lịch sử: Thịnh giải quyết conflict nhánh xoay tại commit 7dbbd03; Hưng giải quyết conflict nhánh HUD màu sắc tại commit 48736da; Duy revert commit d050f29 đẩy bừa lên main bằng commit dc56b3f để thiết lập kỷ luật Git.", "• Giải pháp: ")

    add_h2("3.2. Lỗi thuật toán kiểm tra biên và lệch tọa độ dồn hàng trong removeLine()")
    add_bullet("SV2 duyệt vòng lặp từ j = 0 đến j < W, vô tình kiểm tra cả hai bờ tường bảo vệ. Hàng đầy không bị xóa hoặc xóa luôn cả tường; các dòng phía trên không dồn xuống được.", "• Bản chất: ")
    add_bullet("Nhóm trưởng Duy và SV5 Hưng tổ chức chia sẻ màn hình trên Slack hỗ trợ SV2 viết lại logic: chỉ duyệt trong khoảng lòng sân chơi 1 <= j < W - 1, dịch chuyển các dòng phía trên xuống bằng board[k][j] = board[k-1][j] và xóa trắng hàng trên cùng. Kết quả được kiểm chứng hoàn hảo tại commit 5dbf4b9 và merge qua PR #8.", "• Giải pháp: ")

    add_h2("3.3. Hiện tượng chớp giật màn hình (Screen Flickering) do lạm dụng system('cls')")
    add_bullet("Mỗi chu kỳ game gọi lệnh xóa màn hình cls khiến cửa sổ console bị nhấp nháy dữ dội ở tần số cao, gây mỏi mắt và phản hồi phím trễ.", "• Bản chất: ")
    add_bullet("SV5 Hưng ứng dụng Windows Console API cấp thấp trong ColorRenderer.h: sử dụng SetConsoleCursorPosition đưa con trỏ về tọa độ (0, 0) để vẽ đè trực tiếp lên bộ đệm cũ kết hợp ẩn con trỏ chuột console. Tốc độ khung hình đạt 30 FPS mượt mà tuyệt đối.", "• Giải pháp: ")

    add_h2("3.4. Khối gạch bị kẹt ngoài biên hoặc đè khối khác khi bấm phím xoay")
    add_bullet("Khi xoay khối ở sát mép tường trái hoặc phải, phép quay ma trận đưa tọa độ các khối con vượt ra khỏi biên mảng.", "• Bản chất: ")
    add_bullet("SV4 Thịnh và nhóm tích hợp thuật toán Wall-Kick cơ bản: tự động dịch chuyển khối sang trái/phải 1 ô nếu gặp vật cản; nếu cả hai phía đều kẹt thì hủy lệnh xoay để giữ an toàn tuyệt đối cho bàn cờ. Sau đó Khang hoàn thiện thành phương thức Tetromino::rotated() const trả về bản sao an toàn.", "• Giải pháp: ")

    add_h2("3.5. Lệch pha thời gian làm việc và nguy cơ trễ hạn chót (Deadline)")
    add_bullet("Thời gian rảnh rỗi giữa các thành viên không trùng khớp, dẫn tới việc phản hồi Slack chậm trễ và các PR bị tồn đọng.", "• Bản chất: ")
    add_bullet("Nhóm bổ sung điều khoản: phản hồi Slack tối đa 4 giờ; phân quyền thêm cho Khang làm Co-reviewer; gán nhãn màu cảnh báo Due Date Warning trên Trello đối với các thẻ sắp đến hạn để ưu tiên tối đa.", "• Giải pháp: ")

    # ================= IV. PHÂN CHIA VÀ PHÂN CHIA LẠI CÔNG VIỆC =================
    add_h1("IV. PHÂN CHIA VÀ PHÂN CHIA LẠI CÔNG VIỆC CỦA CÁC THÀNH VIÊN")
    add_body("Sự thành công của dự án khẳng định tầm quan trọng của tính linh hoạt trong quản lý: sẵn sàng tái cấu trúc và phân bổ lại công việc để giải phóng các điểm nghẽn (Bottlenecks) và phát huy tối đa thế mạnh cá nhân.")

    tbl2 = doc.add_table(rows=6, cols=4)
    tbl2.alignment = WD_TABLE_ALIGNMENT.CENTER
    set_table_borders(tbl2)
    
    headers2 = ["Thành viên (MSSV)", "Phân công ban đầu", "Phân chia lại thực tế", "Kết quả & Dẫn chứng Git (Commit / PR)"]
    for i, h in enumerate(headers2):
        tbl2.cell(0, i).paragraphs[0].text = h
    format_row(tbl2.rows[0], is_header=True, bg_color="1E3A8A")
    
    data2 = [
        ("Nguyễn Ngọc Duy\n(26730013 - SV1)", "Khởi tạo repo, quản lý Trello, review code", "Giữ vai trò PM, trực tiếp hỗ trợ SV2 gỡ lỗi, viết lại README, mở rộng Đa nền tảng macOS/Linux", "10 commits, 2 PRs merged (#10, #12), revert dc56b3f bảo vệ main, Platform.h & play.sh (commit 222ff2c)"),
        ("Lê Vũ Thảnh\n(26730061 - SV2)", "Viết hàm removeLine()", "Được nhóm hỗ trợ tinh giản phạm vi: tập trung hoàn thiện chính xác logic mảng xóa hàng", "12 commits, 1 PR merged (#8), 3 PRs closed (#3, #4, #5), commit sửa lỗi 5dbf4b9, commit sync 8284f43"),
        ("Nguyễn Hoàng Khang\n(26730030 - SV3)", "Thiết kế viền vuông và khối vuông", "Hoàn thành viền vuông CP437, làm Co-reviewer và đột phá vai trò Kiến trúc sư Refactor OOP 100%", "16 commits, 1 PR merged (#7: commit 63b108c), 14 commits Refactor OOP (7 class, rút gọn main.cpp còn 17 dòng)"),
        ("Trần Công Thịnh\n(26730064 - SV4)", "Viết hàm xoay khối gạch rotate()", "Hoàn thành xoay khối, nhận nhiệm vụ tự rebase và giải quyết merge conflict cục bộ với main", "4 commits, 1 PR merged (#6), tự giải quyết xung đột code tại commit 7dbbd03 ('fix conflict')"),
        ("Phạm Phú Nguyễn Hưng\n(26730023 - SV5)", "Viết module tăng tốc DropSpeedController", "Mở rộng: HUD màu sắc ANSI, Flicker-Free, Ghost/Hold/Next, tự giải quyết conflict, Unit Test", "15 commits, 3 PRs merged (#1, #9, #11), resolve conflict 48736da, bộ Unit Test test_speed.cpp 6/6 PASS")
    ]
    
    for row_idx, row_data in enumerate(data2, start=1):
        bg = "F8FAFC" if row_idx % 2 == 1 else "FFFFFF"
        for col_idx, val in enumerate(row_data):
            tbl2.cell(row_idx, col_idx).paragraphs[0].text = val
        format_row(tbl2.rows[row_idx], is_header=False, bg_color=bg)

    # ================= V. ĐÁNH GIÁ MỨC ĐỘ ĐÓNG GÓP & BÀI HỌC KINH NGHIỆM =================
    add_h1("V. ĐÁNH GIÁ MỨC ĐỘ ĐÓNG GÓP VÀ BÀI HỌC KINH NGHIỆM")
    
    add_h2("5.1. Bảng đánh giá khối lượng và tỷ lệ đóng góp của các thành viên (SSOT từ Git)")
    
    tbl3 = doc.add_table(rows=6, cols=6)
    tbl3.alignment = WD_TABLE_ALIGNMENT.CENTER
    set_table_borders(tbl3)
    
    headers3 = ["STT", "Họ và Tên", "MSSV", "Minh chứng Git / Trello thực tế", "Tỷ lệ đóng góp", "Xếp loại"]
    for i, h in enumerate(headers3):
        tbl3.cell(0, i).paragraphs[0].text = h
    format_row(tbl3.rows[0], is_header=True, bg_color="1E3A8A")
    
    data3 = [
        ("1", "Nguyễn Ngọc Duy", "26730013", "10 commits, 2 PRs merged (#10, #12), revert dc56b3f, Platform.h, quản trị Kanban", "100%", "Xuất sắc"),
        ("2", "Lê Vũ Thảnh", "26730061", "12 commits, 1 PR merged (#8), 3 PRs closed (#3, #4, #5), commit 5dbf4b9", "100%", "Hoàn thành tốt"),
        ("3", "Nguyễn Hoàng Khang", "26730030", "16 commits, 1 PR merged (#7), 14 commits refactor OOP 7 class, co-reviewer", "100%", "Xuất sắc"),
        ("4", "Trần Công Thịnh", "26730064", "4 commits, 1 PR merged (#6), tự giải quyết xung đột tại commit 7dbbd03", "100%", "Hoàn thành tốt"),
        ("5", "Phạm Phú Nguyễn Hưng", "26730023", "15 commits, 3 PRs merged (#1, #9, #11), conflict 48736da, 6 unit test cases PASS", "100%", "Xuất sắc")
    ]
    
    for row_idx, row_data in enumerate(data3, start=1):
        bg = "F8FAFC" if row_idx % 2 == 1 else "FFFFFF"
        for col_idx, val in enumerate(row_data):
            tbl3.cell(row_idx, col_idx).paragraphs[0].text = val
        format_row(tbl3.rows[row_idx], is_header=False, bg_color=bg)

    add_h2("5.2. Các bài học kinh nghiệm cốt lõi thu nhận được")
    add_bullet("Kiến trúc OOP & Module hóa là bắt buộc: Tránh xa kiến trúc đơn file (God-file). Việc tách các lớp DropSpeedController, ColorRenderer và 7 lớp OOP chuẩn của Khang giúp giảm thiểu 90% nguy cơ dẫm chân lên mã nguồn.", "1. Về Kỹ thuật: ")
    add_bullet("Kỷ luật phân nhánh Git Flow: Luôn fetch và merge origin/main cục bộ trước khi mở PR. Quy chuẩn bắt buộc 2 reviewers giúp lọc sạch lỗi biên mảng trước khi vào nhánh chính.", "2. Về Quy trình: ")
    add_bullet("Văn hóa thấu cảm và hỗ trợ lẫn nhau: Khi một thành viên gặp khó khăn về logic thuật toán, sự tương trợ trực tiếp qua cuộc gọi chia sẻ màn hình hiệu quả gấp nhiều lần việc thúc ép bằng lời nói.", "3. Về Kỹ năng mềm: ")
    add_bullet("Linh hoạt tái cấu trúc công việc: Sẵn sàng điều chỉnh bảng phân công để thích ứng với diễn biến thực tế chính là chìa khóa then chốt giúp dự án về đích an toàn và đúng hẹn.", "4. Về Quản trị: ")

    add_callout(doc, "KẾT LUẬN VÀ NGHIỆM THU",
                "100% thành viên nhóm Hidden Gem đã hoàn thành đầy đủ nghĩa vụ cam kết trong Hợp đồng nhóm, làm chủ toàn diện quy trình làm việc nhóm số hóa qua Git/GitHub, Trello và Slack, mang lại một sản phẩm trò chơi Tetris C++ hoàn thiện, thẩm mỹ và vận hành ổn định.")

    out_path = os.path.abspath("docs/MO_TA_QUA_TRINH_LAM_VIEC_NHOM.docx")
    doc.save(out_path)
    print(f"Báo cáo Word đã được tạo thành công tại: {out_path}")

if __name__ == "__main__":
    create_document()
